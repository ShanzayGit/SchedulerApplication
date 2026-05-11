#define _CRT_SECURE_NO_WARNINGS
#include "Scheduler.h"
#include <sqlite3.h>      // full sqlite3 definition — only in this .cpp
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

// ── static member ─────────────────────────────────────────────────────────────
const Date Schedular::systemDate = Schedular::getCurrentDate();

// ── internal helper: String -> char buffer ────────────────────────────────────
static void toChar(const String& s, char* buf, int maxLen) {
    int len = s.getLength();
    if (len >= maxLen) len = maxLen - 1;
    for (int i = 0; i < len; i++) buf[i] = s[i];
    buf[len] = '\0';
}

// ── getCurrentDate ────────────────────────────────────────────────────────────
Date Schedular::getCurrentDate() {
    time_t now = time(0);
    tm* lt = localtime(&now);
    return Date(1 + lt->tm_mon, lt->tm_mday, 1900 + lt->tm_year);
}

// ── initDB: create table if it doesn't exist ──────────────────────────────────
void Schedular::initDB() {
    if (!db) return;
    const char* sql =
        "CREATE TABLE IF NOT EXISTS tasks ("
        "  id      INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  month   INTEGER NOT NULL,"
        "  day     INTEGER NOT NULL,"
        "  year    INTEGER NOT NULL,"
        "  hour    INTEGER NOT NULL,"
        "  minute  INTEGER NOT NULL,"
        "  second  INTEGER NOT NULL,"
        "  msg     TEXT    NOT NULL,"
        "  status  TEXT    NOT NULL"
        ");";
    char* err = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        cerr << "[DB] Create table failed: " << err << "\n";
        sqlite3_free(err);
    }
}

// ── syncFromDB: load all rows into taskList ───────────────────────────────────
void Schedular::syncFromDB() {
    if (!db) return;
    const char* sql =
        "SELECT month,day,year,hour,minute,second,msg,status FROM tasks;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "[DB] syncFromDB prepare failed: " << sqlite3_errmsg(db) << "\n";
        return;
    }
    noOfTasks = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && noOfTasks < capacity) {
        int mo = sqlite3_column_int(stmt, 0);
        int dy = sqlite3_column_int(stmt, 1);
        int yr = sqlite3_column_int(stmt, 2);
        int hr = sqlite3_column_int(stmt, 3);
        int mn = sqlite3_column_int(stmt, 4);
        int sc = sqlite3_column_int(stmt, 5);
        const char* msg = (const char*)sqlite3_column_text(stmt, 6);
        const char* st = (const char*)sqlite3_column_text(stmt, 7);
        Date   d(mo, dy, yr);
        Time   t; t.setTime(hr, mn, sc);
        String m(msg ? msg : "");
        String s(st ? st : "");
        taskList[noOfTasks++].setTask(d, t, m, s);
    }
    sqlite3_finalize(stmt);
}

// ── constructors ──────────────────────────────────────────────────────────────
Schedular::Schedular() : taskList(nullptr), noOfTasks(0), capacity(64), db(nullptr) {
    taskList = new Task[capacity];
    if (sqlite3_open("scheduler.db", &db) != SQLITE_OK) {
        cerr << "[DB] Could not open scheduler.db: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
    else {
        initDB();
        syncFromDB();
    }
}

Schedular::Schedular(int size)
    : taskList(nullptr), noOfTasks(0), capacity(size), db(nullptr) {
    taskList = new Task[capacity];
    if (sqlite3_open("scheduler.db", &db) != SQLITE_OK) {
        cerr << "[DB] Could not open scheduler.db: " << sqlite3_errmsg(db) << "\n";
        db = nullptr;
    }
    else {
        initDB();
        syncFromDB();
    }
}

Schedular::~Schedular() {
    if (db) sqlite3_close(db);
    delete[] taskList;
    db = nullptr;
    taskList = nullptr;
    noOfTasks = 0;
    capacity = 0;
}

// ── addTask ───────────────────────────────────────────────────────────────────
void Schedular::addTask(const Task& t) {
    // 1. Insert into DB
    if (db) {
        const char* sql =
            "INSERT INTO tasks (month,day,year,hour,minute,second,msg,status)"
            " VALUES (?,?,?,?,?,?,?,?);";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            char mb[512], sb[64];
            toChar(t.getMsg(), mb, 512);
            toChar(t.getStatus(), sb, 64);
            sqlite3_bind_int(stmt, 1, t.getDate().getMonth());
            sqlite3_bind_int(stmt, 2, t.getDate().getDay());
            sqlite3_bind_int(stmt, 3, t.getDate().getYear());
            sqlite3_bind_int(stmt, 4, t.getTime().getHour());
            sqlite3_bind_int(stmt, 5, t.getTime().getMinute());
            sqlite3_bind_int(stmt, 6, t.getTime().getSecond());
            sqlite3_bind_text(stmt, 7, mb, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 8, sb, -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) != SQLITE_DONE)
                cerr << "[DB] Insert failed: " << sqlite3_errmsg(db) << "\n";
            sqlite3_finalize(stmt);
        }
    }
    // 2. Keep in-memory list in sync
    if (noOfTasks >= capacity) reSize(capacity + 2);
    taskList[noOfTasks++].setTask(t.getDate(), t.getTime(),
        t.getMsg(), t.getStatus());
}

// ── updateTaskTime ────────────────────────────────────────────────────────────
void Schedular::updateTaskTime(const Date& d, const String& s, const Time& newT) {
    if (db) {
        const char* sql =
            "UPDATE tasks SET hour=?,minute=?,second=?"
            " WHERE month=? AND day=? AND year=? AND msg=?;";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            char mb[512]; toChar(s, mb, 512);
            sqlite3_bind_int(stmt, 1, newT.getHour());
            sqlite3_bind_int(stmt, 2, newT.getMinute());
            sqlite3_bind_int(stmt, 3, newT.getSecond());
            sqlite3_bind_int(stmt, 4, d.getMonth());
            sqlite3_bind_int(stmt, 5, d.getDay());
            sqlite3_bind_int(stmt, 6, d.getYear());
            sqlite3_bind_text(stmt, 7, mb, -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getMsg() == s &&
            taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear()) {
            taskList[i].updateTime(newT); found = true;
        }
    }
    if (!found) cout << "No Task Matches the Search!!\n";
}

// ── updateTaskDate ────────────────────────────────────────────────────────────
void Schedular::updateTaskDate(const String& m, const Date& d, const Date& newD) {
    if (db) {
        const char* sql =
            "UPDATE tasks SET month=?,day=?,year=?"
            " WHERE month=? AND day=? AND year=? AND msg=?;";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            char mb[512]; toChar(m, mb, 512);
            sqlite3_bind_int(stmt, 1, newD.getMonth());
            sqlite3_bind_int(stmt, 2, newD.getDay());
            sqlite3_bind_int(stmt, 3, newD.getYear());
            sqlite3_bind_int(stmt, 4, d.getMonth());
            sqlite3_bind_int(stmt, 5, d.getDay());
            sqlite3_bind_int(stmt, 6, d.getYear());
            sqlite3_bind_text(stmt, 7, mb, -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getMsg() == m &&
            taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear()) {
            taskList[i].updateDate(newD); found = true;
        }
    }
    if (!found) cout << "No Date Matches the Search!!\n";
}

// ── updateTaskMsg ─────────────────────────────────────────────────────────────
void Schedular::updateTaskMsg(const Date& d, const String& m, const String& newM) {
    if (db) {
        const char* sql =
            "UPDATE tasks SET msg=?"
            " WHERE month=? AND day=? AND year=? AND msg=?;";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            char ob[512], nb[512];
            toChar(m, ob, 512);
            toChar(newM, nb, 512);
            sqlite3_bind_text(stmt, 1, nb, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, d.getMonth());
            sqlite3_bind_int(stmt, 3, d.getDay());
            sqlite3_bind_int(stmt, 4, d.getYear());
            sqlite3_bind_text(stmt, 5, ob, -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getMsg() == m &&
            taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear()) {
            taskList[i].updateMessage(newM); found = true;
        }
    }
    if (!found) cout << "No Task Matches the Search!!\n";
}

// ── updateTaskStatus ──────────────────────────────────────────────────────────
void Schedular::updateTaskStatus(const Date& d, const String& m, const String& s) {
    if (db) {
        const char* sql =
            "UPDATE tasks SET status=?"
            " WHERE month=? AND day=? AND year=? AND msg=?;";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            char mb[512], sb[64];
            toChar(m, mb, 512);
            toChar(s, sb, 64);
            sqlite3_bind_text(stmt, 1, sb, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, d.getMonth());
            sqlite3_bind_int(stmt, 3, d.getDay());
            sqlite3_bind_int(stmt, 4, d.getYear());
            sqlite3_bind_text(stmt, 5, mb, -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getMsg() == m &&
            taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear()) {
            taskList[i].updateStatus(s); found = true;
        }
    }
    if (!found) cout << "No Task Matches the Search!!\n";
}

// ── display methods ───────────────────────────────────────────────────────────
void Schedular::displayTask(const Date& d) const {
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear()) {
            cout << "Task   : " << taskList[i].getMsg() << "\n"
                << "Status : " << taskList[i].getStatus() << "\n"
                << "Time   : ";
            taskList[i].getTime().printTwelveHourFormat();
            cout << "\n";
            found = true;
        }
    }
    if (!found) cout << "No Task Matches your Search!!\n";
}

void Schedular::DisplayTodaysTask() const {
    int mo = systemDate.getMonth(), dy = systemDate.getDay(),
        yr = systemDate.getYear();
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getDate().getMonth() == mo &&
            taskList[i].getDate().getDay() == dy &&
            taskList[i].getDate().getYear() == yr) {
            cout << "Today's Task : " << taskList[i].getMsg() << "\n"
                << "Status       : " << taskList[i].getStatus() << "\n"
                << "Time         : ";
            taskList[i].getTime().printTwelveHourFormat();
            cout << "\n";
            found = true;
        }
    }
    if (!found) cout << "No Task Scheduled for Today!!\n";
}

void Schedular::displayTodoTasks() const {
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getStatus() == "Todo") {
            cout << "\nDate : "; taskList[i].getDate().printFormat1();
            cout << "\nTime : "; taskList[i].getTime().printTwelveHourFormat();
            cout << "\nTask : " << taskList[i].getMsg() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No Todo Tasks!\n";
}

void Schedular::displayInProgressTasks() const {
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getStatus() == "InProgress") {
            cout << "\nDate : "; taskList[i].getDate().printFormat1();
            cout << "\nTime : "; taskList[i].getTime().printTwelveHourFormat();
            cout << "\nTask : " << taskList[i].getMsg() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No InProgress Tasks!\n";
}

void Schedular::displayDoneTasks() const {
    bool found = false;
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getStatus() == "Done") {
            cout << "\nDate : "; taskList[i].getDate().printFormat1();
            cout << "\nTime : "; taskList[i].getTime().printTwelveHourFormat();
            cout << "\nTask : " << taskList[i].getMsg() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No Done Tasks!\n";
}

void Schedular::displayAllTasks() const {
    if (noOfTasks == 0) { cout << "No Tasks!\n"; return; }
    for (int i = 0; i < noOfTasks; i++) {
        cout << "\n[" << (i + 1) << "] Date   : ";
        taskList[i].getDate().printFormat1();
        cout << "\n    Time   : "; taskList[i].getTime().printTwelveHourFormat();
        cout << "\n    Task   : " << taskList[i].getMsg();
        cout << "\n    Status : " << taskList[i].getStatus() << "\n";
    }
}

// ── DateMatchIndex / reSize ───────────────────────────────────────────────────
int Schedular::DateMatchIndex(const Date& d) const {
    for (int i = 0; i < noOfTasks; i++) {
        if (taskList[i].getDate().getMonth() == d.getMonth() &&
            taskList[i].getDate().getDay() == d.getDay() &&
            taskList[i].getDate().getYear() == d.getYear())
            return i;
    }
    return -1;
}

void Schedular::reSize(int cap) {
    Task* temp = new Task[cap];
    int   copy = (cap < noOfTasks) ? cap : noOfTasks;
    for (int i = 0; i < copy; i++)
        temp[i].setTask(taskList[i].getDate(), taskList[i].getTime(),
            taskList[i].getMsg(), taskList[i].getStatus());
    delete[] taskList;
    taskList = temp;
    capacity = cap;
    noOfTasks = copy;
}

// ── loadTasksInto (Qt GUI bridge) ─────────────────────────────────────────────
int Schedular::loadTasksInto(Task* out, int maxCount,
    const char* status,
    const Date* date) const
{
    int count = 0;
    for (int i = 0; i < noOfTasks && count < maxCount; i++) {
        // Date filter
        if (date != nullptr) {
            if (taskList[i].getDate().getMonth() != date->getMonth() ||
                taskList[i].getDate().getDay() != date->getDay() ||
                taskList[i].getDate().getYear() != date->getYear())
                continue;
        }
        // Status filter
        if (status != nullptr) {
            String st(status);
            if (!(taskList[i].getStatus() == st))
                continue;
        }
        out[count++].setTask(taskList[i].getDate(), taskList[i].getTime(),
            taskList[i].getMsg(), taskList[i].getStatus());
    }
    return count;
}