#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include "MyTime.h"
#include "MyString.h"
#include "Date.h"
#include "Task.h"

// sqlite3 is an opaque struct — forward declare so the header
// compiles without needing sqlite3.h everywhere.
struct sqlite3;

class Schedular {
    Task* taskList;
    int      noOfTasks;
    int      capacity;
    sqlite3* db;           // raw SQLite handle — defined in sqlite3.h

    static const Date systemDate;
    int  DateMatchIndex(const Date& d) const;
    void syncFromDB();
    void initDB();         // create table if not exists

public:
    Schedular();
    Schedular(int);
    ~Schedular();

    void updateTaskTime(const Date& d, const String& s, const Time& newT);
    void updateTaskDate(const String& s, const Date& oldD, const Date& newD);
    void updateTaskMsg(const Date& d, const String& m, const String& newM);
    void updateTaskStatus(const Date& d, const String& m, const String& s);

    static Date getCurrentDate();

    void addTask(const Task&);
    void displayTask(const Date& d = systemDate) const;
    void DisplayTodaysTask()      const;
    void displayTodoTasks()       const;
    void displayAllTasks()        const;
    void displayInProgressTasks() const;
    void displayDoneTasks()       const;
    void reSize(int);


    // Qt GUI bridge: copy matching tasks into caller-supplied array.
    // Pass status=nullptr to skip status filter.
    // Pass date=nullptr  to skip date filter.
    // Returns number copied.
    int loadTasksInto(Task* out, int maxCount,
        const char* status = nullptr,
        const Date* date = nullptr) const;
    int getCapacity() const { return capacity; }
    int getTasks()    const { return noOfTasks; }
};

#endif

// Qt GUI bridge: copy matching tasks into caller-supplied array.
// Pass status=nullptr to skip status filter.
// Pass date=nullptr to skip date filter.
// Returns number of tasks copied.
//
//const char* status = nullptr,
//const Date* date = nullptr; const;