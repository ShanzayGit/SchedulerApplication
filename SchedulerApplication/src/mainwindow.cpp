#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_homepage.h"
#include "ui_addtaskspage.h"
#include "ui_updatetaskspage.h"
#include "ui_viewtaskspage.h"
#include "ui_updatedatepage.h"
#include "ui_updatemessagepage.h"
#include "ui_updatestatuspage.h"
#include "ui_updatetimepage.h"
#include "ui_viewallpage.h"
#include "ui_viewdonepage.h"
#include "ui_viewinprogresspage.h"
#include "ui_viewspecificpage.h"
#include "ui_viewtodaypage.h"
#include "ui_viewtodopage.h"

#include "Scheduler.h"
#include "MyString.h"
#include "Date.h"
#include "MyTime.h"
#include "Task.h"

#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDate>
#include <QTime>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <cstring>

// ??? Page wrapper classes ?????????????????????????????????????????????????????

class HomePage : public QWidget {
public:
    Ui::HomePage ui;
    HomePage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class AddTasksPage : public QWidget {
public:
    Ui::AddTasksPage ui;
    AddTasksPage(QWidget* p = nullptr) : QWidget(p) {
        ui.setupUi(this);
        ui.comboBox->addItems({ "Todo", "InProgress", "Done" });
    }
};
class UpdateTasksPage : public QWidget {
public:
    Ui::UpdateTasksPage ui;
    UpdateTasksPage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class ViewTasksPage : public QWidget {
public:
    Ui::ViewTasksPage ui;
    ViewTasksPage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class updatedatepage : public QWidget {
public:
    Ui::updatedatepage ui;
    updatedatepage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class updatemessagepage : public QWidget {
public:
    Ui::updatemessagepage ui;
    updatemessagepage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class updatestatuspage : public QWidget {
public:
    Ui::updatestatuspage ui;
    updatestatuspage(QWidget* p = nullptr) : QWidget(p) {
        ui.setupUi(this);
        ui.comboBox->addItems({ "Todo", "InProgress", "Done" });
    }
};
class updatetimepage : public QWidget {
public:
    Ui::updatetimepage ui;
    updatetimepage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewallpage : public QWidget {
public:
    Ui::viewallpage ui;
    viewallpage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewdonepage : public QWidget {
public:
    Ui::viewdonepage ui;
    viewdonepage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewinprogresspage : public QWidget {
public:
    Ui::viewinprogresspage ui;
    viewinprogresspage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewspecificpage : public QWidget {
public:
    Ui::viewspecificpage ui;
    viewspecificpage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewtodaypage : public QWidget {
public:
    Ui::viewtodaypage ui;
    viewtodaypage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};
class viewtodopage : public QWidget {
public:
    Ui::viewtodopage ui;
    viewtodopage(QWidget* p = nullptr) : QWidget(p) { ui.setupUi(this); }
};

// ??? Task detail popup ????????????????????????????????????????????????????????
// Shows a styled QDialog with full task info when a row is clicked.

static void showTaskDetail(QWidget* parent, Task* taskBuf, int row)
{
    if (row < 0) return;

    Date   d = taskBuf[row].getDate();
    Time   t = taskBuf[row].getTime();
    String msg = taskBuf[row].getMsg();
    String st = taskBuf[row].getStatus();

    // Build display strings
    QString dateStr = QString("%1/%2/%3")
        .arg(d.getMonth(), 2, 10, QChar('0'))
        .arg(d.getDay(), 2, 10, QChar('0'))
        .arg(d.getYear());

    int h = t.getHour(), m = t.getMinute(), s = t.getSecond();
    int h12 = h % 12; if (h12 == 0) h12 = 12;
    QString timeStr = QString("%1:%2:%3 %4")
        .arg(h12, 2, 10, QChar('0'))
        .arg(m, 2, 10, QChar('0'))
        .arg(s, 2, 10, QChar('0'))
        .arg(h < 12 ? "AM" : "PM");

    char mb[512] = {}, sb[64] = {};// Convert String to QByteArray safely
    //QByteArray msgBytes(msg.c_str(), msg.getLength());
    //QByteArray stBytes(st.c_str(), st.getLength());

    //// Ensure null termination
    //msgBytes.append('\0');
    //stBytes.append('\0');

    // Build QStrings directly
    QString msgStr = QString::fromUtf8(msg.c_str());
    QString stStr = QString::fromUtf8(st.c_str());

    //QString msgStr = QString::fromUtf8(mb);
    //QString stStr = QString::fromUtf8(sb);

    // Status badge colour
    QString badgeColor = "#aaa";
    if (stStr == "Todo")       badgeColor = "#F2C6DE";
    if (stStr == "InProgress") badgeColor = "#C6DEF1";
    if (stStr == "Done")       badgeColor = "#C9E4DE";

    // ?? Build dialog ??????????????????????????????????????????????????????????
    QDialog* dlg = new QDialog(parent);
    dlg->setWindowTitle("Task Detail");
    dlg->setFixedSize(420, 320);
    dlg->setStyleSheet(R"(
        QDialog {
            background-color: #fdf1f1;
        }
        QLabel#titleLabel {
            font-size: 15px;
            font-weight: bold;
            color: #2e2e2e;
        }
        QFrame#card {
            background-color: white;
            border-radius: 10px;
            border: 1px solid #ddd;
        }
        QLabel {
            color: #2e2e2e;
            font-size: 13px;
        }
        QLabel#keyLabel {
            color: #888;
            font-size: 12px;
        }
        QPushButton {
            background-color: #d8f3dc;
            border-radius: 8px;
            padding: 6px 20px;
            font-size: 13px;
        }
        QPushButton:pressed { background-color: #b7dfc0; }
    )");

    QVBoxLayout* root = new QVBoxLayout(dlg);
    root->setContentsMargins(20, 16, 20, 16);
    root->setSpacing(12);

    // Title
    QLabel* title = new QLabel("Task Details", dlg);
    title->setObjectName("titleLabel");
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);

    // Card frame
    QFrame* card = new QFrame(dlg);
    card->setObjectName("card");
    QVBoxLayout* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(18, 14, 18, 14);
    cardLayout->setSpacing(10);

    // Helper: add a key-value row inside the card
    auto addRow = [&](const QString& key, const QString& value) {
        QHBoxLayout* row = new QHBoxLayout();
        QLabel* k = new QLabel(key + ":", card);
        k->setObjectName("keyLabel");
        k->setFixedWidth(80);
        QLabel* v = new QLabel(value, card);
        v->setWordWrap(true);
        row->addWidget(k);
        row->addWidget(v, 1);
        cardLayout->addLayout(row);
        };

    addRow("Message", msgStr);
    addRow("Date", dateStr);
    addRow("Time", timeStr);

    // Status badge
    QHBoxLayout* stRow = new QHBoxLayout();
    QLabel* stKey = new QLabel("Status:", card);
    stKey->setObjectName("keyLabel");
    stKey->setFixedWidth(80);
    QLabel* stVal = new QLabel(stStr, card);
    stVal->setStyleSheet(QString(
        "background-color: %1; border-radius: 6px;"
        "padding: 2px 10px; font-weight: bold;").arg(badgeColor));
    stVal->setFixedHeight(24);
    stRow->addWidget(stKey);
    stRow->addWidget(stVal);
    stRow->addStretch();
    cardLayout->addLayout(stRow);

    root->addWidget(card, 1);

    // Close button
    QHBoxLayout* btnRow = new QHBoxLayout();
    btnRow->addStretch();
    QPushButton* closeBtn = new QPushButton("Close", dlg);
    closeBtn->setFixedWidth(90);
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    btnRow->addWidget(closeBtn);
    root->addLayout(btnRow);

    dlg->exec();         // modal — blocks until closed
    dlg->deleteLater();
}

// ??? Table helpers ????????????????????????????????????????????????????????????

static void fillTable(QTableWidget* table, Task* tasks, int count)
{
    table->clearContents();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({ "Date", "Time", "Message", "Status" });
    table->setRowCount(count);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    // Hint shown when table is empty
    if (count == 0) {
        table->setRowCount(1);
        QTableWidgetItem* empty = new QTableWidgetItem("No tasks found.");
        empty->setTextAlignment(Qt::AlignCenter);
        empty->setFlags(Qt::ItemIsEnabled);
        table->setSpan(0, 0, 1, 4);
        table->setItem(0, 0, empty);
        return;
    }

    for (int i = 0; i < count; i++) {
        Date   d = tasks[i].getDate();
        Time   t = tasks[i].getTime();
        String msg = tasks[i].getMsg();
        String st = tasks[i].getStatus();

        QString dateStr = QString("%1/%2/%3")
            .arg(d.getMonth(), 2, 10, QChar('0'))
            .arg(d.getDay(), 2, 10, QChar('0'))
            .arg(d.getYear());

        int h = t.getHour(), mi = t.getMinute(), s = t.getSecond();
        int h12 = h % 12; if (h12 == 0) h12 = 12;
        QString timeStr = QString("%1:%2:%3 %4")
            .arg(h12, 2, 10, QChar('0'))
            .arg(mi, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'))
            .arg(h < 12 ? "AM" : "PM");

        char mb[512] = {}, sb[64] = {};
        for (int k = 0; k < msg.getLength() && k < 511; k++) mb[k] = msg[k];
        for (int k = 0; k < st.getLength() && k < 63; k++) sb[k] = st[k];

        table->setItem(i, 0, new QTableWidgetItem(dateStr));
        table->setItem(i, 1, new QTableWidgetItem(timeStr));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromUtf8(mb)));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(sb)));

        // Style status cell
        QString stStr = QString::fromUtf8(sb);
        QColor  bg = QColor("#f5f5f5");
        if (stStr == "Todo")       bg = QColor("#F2C6DE");
        if (stStr == "InProgress") bg = QColor("#C6DEF1");
        if (stStr == "Done")       bg = QColor("#C9E4DE");
        if (table->item(i, 3)) table->item(i, 3)->setBackground(bg);
    }
}

// Connect cellClicked on a table to show the detail popup.
// taskStore: pointer to the static Task[256] buffer for that page.
static void connectTableClick(QTableWidget* table, Task* taskStore, QWidget* parent)
{
    // Disconnect any previous connections to avoid duplicates on re-open
    QObject::disconnect(table, &QTableWidget::cellClicked, nullptr, nullptr);

    QObject::connect(table, &QTableWidget::cellClicked,
        parent, [table, taskStore, parent](int row, int /*col*/) {
            // Ignore the "No tasks found." placeholder row
            if (table->columnSpan(0, 0) == 4) return;
            showTaskDetail(parent, taskStore, row);
        });
}

// QString ? char buffer
static void toChar(const QString& qs, char* buf, int maxLen)
{
    QByteArray ba = qs.toUtf8();
    int len = ba.size();
    if (len >= maxLen) len = maxLen - 1;
    memcpy(buf, ba.constData(), len);
    buf[len] = '\0';
}

// ??? MainWindow ???????????????????????????????????????????????????????????????

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sched()
{
    ui->setupUi(this);
    setWindowTitle("Task Scheduler");
    stack = ui->stackedWidget;
    setupPages();
    connectSignals();
    stack->setCurrentIndex(PAGE_HOME);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPages()
{
    homePage = new HomePage(this);
    addTasksPage = new AddTasksPage(this);
    updateTasksPage = new UpdateTasksPage(this);
    viewTasksPage = new ViewTasksPage(this);
    updateDatePage = new updatedatepage(this);
    updateMessagePage = new updatemessagepage(this);
    updateStatusPage = new updatestatuspage(this);
    updateTimePage = new updatetimepage(this);
    viewAllPage = new viewallpage(this);
    viewDonePage = new viewdonepage(this);
    viewInProgressPage = new viewinprogresspage(this);
    viewSpecificPage = new viewspecificpage(this);
    viewTodayPage = new viewtodaypage(this);
    viewTodoPage = new viewtodopage(this);

    stack->insertWidget(PAGE_HOME, homePage);
    stack->insertWidget(PAGE_ADD_TASK, addTasksPage);
    stack->insertWidget(PAGE_UPDATE_TASKS, updateTasksPage);
    stack->insertWidget(PAGE_VIEW_TASKS, viewTasksPage);
    stack->insertWidget(PAGE_UPDATE_DATE, updateDatePage);
    stack->insertWidget(PAGE_UPDATE_MSG, updateMessagePage);
    stack->insertWidget(PAGE_UPDATE_STATUS, updateStatusPage);
    stack->insertWidget(PAGE_UPDATE_TIME, updateTimePage);
    stack->insertWidget(PAGE_VIEW_ALL, viewAllPage);
    stack->insertWidget(PAGE_VIEW_DONE, viewDonePage);
    stack->insertWidget(PAGE_VIEW_INPROGRESS, viewInProgressPage);
    stack->insertWidget(PAGE_VIEW_SPECIFIC, viewSpecificPage);
    stack->insertWidget(PAGE_VIEW_TODAY, viewTodayPage);
    stack->insertWidget(PAGE_VIEW_TODO, viewTodoPage);
}

void MainWindow::connectSignals()
{
    // ?? HomePage ??????????????????????????????????????????????????????????????
    connect(homePage->ui.btnAddTask, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_ADD_TASK);
        });
    connect(homePage->ui.btnUpdateTask, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TASKS);
        });
    connect(homePage->ui.btnViewTasks, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_VIEW_TASKS);
        });

    // ?? AddTasksPage ??????????????????????????????????????????????????????????
    connect(addTasksPage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_HOME);
        });
    connect(addTasksPage->ui.pushButton, &QPushButton::clicked, this, [this] {
        QDate   qd = addTasksPage->ui.dateEdit->date();
        QTime   qt = addTasksPage->ui.timeEdit->time();
        QString msg = addTasksPage->ui.plainTextEdit->toPlainText().trimmed();
        QString st = addTasksPage->ui.comboBox->currentText();
        if (msg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Task message cannot be empty.");
            return;
        }
        char mb[512], sb[64];
        toChar(msg, mb, 512);
        toChar(st, sb, 64);
        Date d(qd.month(), qd.day(), qd.year());
        Time t; t.setTime(qt.hour(), qt.minute(), qt.second());
        Task task(d, t, String(mb), String(sb));
        sched.addTask(task);
        QMessageBox::information(this, "Success", "Task added successfully!");
        addTasksPage->ui.plainTextEdit->setPlainText("Type your message here.");
        });

    // ?? UpdateTasksPage ???????????????????????????????????????????????????????
    connect(updateTasksPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_HOME); });
    connect(updateTasksPage->ui.btnUpdateMsg, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_MSG); });
    connect(updateTasksPage->ui.btnUpdateTime, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_TIME); });
    connect(updateTasksPage->ui.btnUpdateStatus, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_STATUS); });
    connect(updateTasksPage->ui.btnUpdateDate, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_DATE); });

    // ?? UpdateMessagePage ?????????????????????????????????????????????????????
    connect(updateMessagePage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_TASKS); });
    connect(updateMessagePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateMessagePage->ui.dateEdit->date();
        QString oldMsg = updateMessagePage->ui.plainTextEdit_2->toPlainText().trimmed();
        QString newMsg = updateMessagePage->ui.plainTextEdit_3->toPlainText().trimmed();
        if (oldMsg.isEmpty() || newMsg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Messages cannot be empty.");
            return;
        }
        char ob[512], nb[512];
        toChar(oldMsg, ob, 512); toChar(newMsg, nb, 512);
        Date d(qd.month(), qd.day(), qd.year());
        sched.updateTaskMsg(d, String(ob), String(nb));
        QMessageBox::information(this, "Success", "Message updated!");
        });

    // ?? UpdateTimePage ????????????????????????????????????????????????????????
    connect(updateTimePage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_TASKS); });
    connect(updateTimePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateTimePage->ui.dateEdit->date();
        QTime   qt = updateTimePage->ui.timeEdit->time();
        QString msg = updateTimePage->ui.plainTextEdit_2->toPlainText().trimmed();
        if (msg.isEmpty()) { QMessageBox::warning(this, "Input Error", "Message cannot be empty."); return; }
        char mb[512]; toChar(msg, mb, 512);
        Date d(qd.month(), qd.day(), qd.year());
        Time t; t.setTime(qt.hour(), qt.minute(), qt.second());
        sched.updateTaskTime(d, String(mb), t);
        QMessageBox::information(this, "Success", "Time updated!");
        });

    // ?? UpdateStatusPage ??????????????????????????????????????????????????????
    connect(updateStatusPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_TASKS); });
    connect(updateStatusPage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateStatusPage->ui.dateEdit->date();
        QString msg = updateStatusPage->ui.plainTextEdit_2->toPlainText().trimmed();
        QString st = updateStatusPage->ui.comboBox->currentText();
        if (msg.isEmpty()) { QMessageBox::warning(this, "Input Error", "Message cannot be empty."); return; }
        char mb[512], sb[64];
        toChar(msg, mb, 512); toChar(st, sb, 64);
        Date d(qd.month(), qd.day(), qd.year());
        sched.updateTaskStatus(d, String(mb), String(sb));
        QMessageBox::information(this, "Success", "Status updated!");
        });

    // ?? UpdateDatePage ????????????????????????????????????????????????????????
    connect(updateDatePage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_UPDATE_TASKS); });
    connect(updateDatePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QString msg = updateDatePage->ui.plainTextEdit->toPlainText().trimmed();
        QDate   qOld = updateDatePage->ui.dateEdit->date();
        QDate   qNew = updateDatePage->ui.dateEdit_2->date();
        if (msg.isEmpty()) { QMessageBox::warning(this, "Input Error", "Message cannot be empty."); return; }
        char mb[512]; toChar(msg, mb, 512);
        Date oldD(qOld.month(), qOld.day(), qOld.year());
        Date newD(qNew.month(), qNew.day(), qNew.year());
        sched.updateTaskDate(String(mb), oldD, newD);
        QMessageBox::information(this, "Success", "Date updated!");
        });

    // ?? ViewTasksPage ?????????????????????????????????????????????????????????
    connect(viewTasksPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_HOME); });

    // View All
    connect(viewTasksPage->ui.btnViewAll, &QPushButton::clicked, this, [this] {
        int n = sched.loadTasksInto(taskBufAll, 256);
        fillTable(viewAllPage->ui.tableWidget, taskBufAll, n);
        viewAllPage->ui.tableWidget->raise();
        connectTableClick(viewAllPage->ui.tableWidget, taskBufAll, this);
        stack->setCurrentIndex(PAGE_VIEW_ALL);
        });

    // View Done
    connect(viewTasksPage->ui.btnViewDone, &QPushButton::clicked, this, [this] {
        int n = sched.loadTasksInto(taskBufDone, 256, "Done");
        fillTable(viewDonePage->ui.tableWidget, taskBufDone, n);
        viewDonePage->ui.tableWidget->raise();
        connectTableClick(viewDonePage->ui.tableWidget, taskBufDone, this);
        stack->setCurrentIndex(PAGE_VIEW_DONE);
        });

    // View Todo
    connect(viewTasksPage->ui.btnViewToDo, &QPushButton::clicked, this, [this] {
        int n = sched.loadTasksInto(taskBufTodo, 256, "Todo");
        fillTable(viewTodoPage->ui.tableWidget, taskBufTodo, n);
        viewTodoPage->ui.tableWidget->raise();
        connectTableClick(viewTodoPage->ui.tableWidget, taskBufTodo, this);
        stack->setCurrentIndex(PAGE_VIEW_TODO);
        });

    // View InProgress
    connect(viewTasksPage->ui.btnViewInProgress, &QPushButton::clicked, this, [this] {
        int n = sched.loadTasksInto(taskBufInProgress, 256, "InProgress");
        fillTable(viewInProgressPage->ui.tableWidget, taskBufInProgress, n);
        viewInProgressPage->ui.tableWidget->raise();
        connectTableClick(viewInProgressPage->ui.tableWidget, taskBufInProgress, this);
        stack->setCurrentIndex(PAGE_VIEW_INPROGRESS);
        });

    // View Today
    connect(viewTasksPage->ui.btnViewToday, &QPushButton::clicked, this, [this] {
        Date today = Schedular::getCurrentDate();
        int n = sched.loadTasksInto(taskBufToday, 256, nullptr, &today);
        fillTable(viewTodayPage->ui.tableWidget, taskBufToday, n);
        viewTodayPage->ui.tableWidget->raise();
        connectTableClick(viewTodayPage->ui.tableWidget, taskBufToday, this);
        stack->setCurrentIndex(PAGE_VIEW_TODAY);
        });

    // View Specific

    connect(viewTasksPage->ui.btnViewSpecific, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_VIEW_SPECIFIC);
        });
    connect(viewSpecificPage->ui.dateEdit, &QDateEdit::dateChanged,
        this, [this](const QDate& qd) {
            Date d(qd.month(), qd.day(), qd.year());
            int n = sched.loadTasksInto(taskBufSpecific, 256, nullptr, &d);
            fillTable(viewSpecificPage->ui.tableWidget, taskBufSpecific, n);
            viewSpecificPage->ui.tableWidget->raise();
            if (viewSpecificPage->ui.tableWidget->rowCount() > 0)
                connectTableClick(viewSpecificPage->ui.tableWidget, taskBufSpecific, this);
        });

    // ?? Back buttons on all view pages ????????????????????????????????????????
    connect(viewAllPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewDonePage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewTodoPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewInProgressPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewTodayPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewSpecificPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
}