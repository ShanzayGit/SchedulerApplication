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
#include <QDate>
#include <QTime>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <cstring>

// ??? Page wrapper classes ?????????????????????????????????????????????????????
// Each is a plain QWidget that owns its Ui object.

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

// ??? Helpers ??????????????????????????????????????????????????????????????????

// Fill a QTableWidget from an array of Tasks
static void fillTable(QTableWidget* table, Task* tasks, int count)
{
    table->clearContents();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({ "Date", "Time", "Message", "Status" });
    table->setRowCount(count);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < count; i++) {
        Date   d = tasks[i].getDate();
        Time   t = tasks[i].getTime();
        String msg = tasks[i].getMsg();
        String st = tasks[i].getStatus();

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

        char mb[512] = {}, sb[64] = {};
        for (int k = 0; k < msg.getLength() && k < 511; k++) mb[k] = msg[k];
        for (int k = 0; k < st.getLength() && k < 63; k++) sb[k] = st[k];

        table->setItem(i, 0, new QTableWidgetItem(dateStr));
        table->setItem(i, 1, new QTableWidgetItem(timeStr));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromUtf8(mb)));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromUtf8(sb)));
    }
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
    , sched()           // Schedular constructed here — opens scheduler.db
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

    // Order MUST match the Pages enum
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

// All lambdas capture [this] only — sched is now a member so no static issues
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

    // ?? UpdateTasksPage sub-menu ??????????????????????????????????????????????
    connect(updateTasksPage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_HOME);
        });
    connect(updateTasksPage->ui.btnUpdateMsg, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_MSG);
        });
    connect(updateTasksPage->ui.btnUpdateTime, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TIME);
        });
    connect(updateTasksPage->ui.btnUpdateStatus, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_STATUS);
        });
    connect(updateTasksPage->ui.btnUpdateDate, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_DATE);
        });

    // ?? UpdateMessagePage ?????????????????????????????????????????????????????
    connect(updateMessagePage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TASKS);
        });
    connect(updateMessagePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateMessagePage->ui.dateEdit->date();
        QString oldMsg = updateMessagePage->ui.plainTextEdit_2->toPlainText().trimmed();
        QString newMsg = updateMessagePage->ui.plainTextEdit_3->toPlainText().trimmed();
        if (oldMsg.isEmpty() || newMsg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Messages cannot be empty.");
            return;
        }
        char ob[512], nb[512];
        toChar(oldMsg, ob, 512);
        toChar(newMsg, nb, 512);
        Date d(qd.month(), qd.day(), qd.year());
        sched.updateTaskMsg(d, String(ob), String(nb));
        QMessageBox::information(this, "Success", "Message updated!");
        });

    // ?? UpdateTimePage ????????????????????????????????????????????????????????
    connect(updateTimePage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TASKS);
        });
    connect(updateTimePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateTimePage->ui.dateEdit->date();
        QTime   qt = updateTimePage->ui.timeEdit->time();
        QString msg = updateTimePage->ui.plainTextEdit_2->toPlainText().trimmed();
        if (msg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Message cannot be empty.");
            return;
        }
        char mb[512]; toChar(msg, mb, 512);
        Date d(qd.month(), qd.day(), qd.year());
        Time t; t.setTime(qt.hour(), qt.minute(), qt.second());
        sched.updateTaskTime(d, String(mb), t);
        QMessageBox::information(this, "Success", "Time updated!");
        });

    // ?? UpdateStatusPage ??????????????????????????????????????????????????????
    connect(updateStatusPage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TASKS);
        });
    connect(updateStatusPage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QDate   qd = updateStatusPage->ui.dateEdit->date();
        QString msg = updateStatusPage->ui.plainTextEdit_2->toPlainText().trimmed();
        QString st = updateStatusPage->ui.comboBox->currentText();
        if (msg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Message cannot be empty.");
            return;
        }
        char mb[512], sb[64];
        toChar(msg, mb, 512);
        toChar(st, sb, 64);
        Date d(qd.month(), qd.day(), qd.year());
        sched.updateTaskStatus(d, String(mb), String(sb));
        QMessageBox::information(this, "Success", "Status updated!");
        });

    // ?? UpdateDatePage ????????????????????????????????????????????????????????
    connect(updateDatePage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_UPDATE_TASKS);
        });
    connect(updateDatePage->ui.btnUpdate, &QPushButton::clicked, this, [this] {
        QString msg = updateDatePage->ui.plainTextEdit->toPlainText().trimmed();
        QDate   qOld = updateDatePage->ui.dateEdit->date();
        QDate   qNew = updateDatePage->ui.dateEdit_2->date();
        if (msg.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Message cannot be empty.");
            return;
        }
        char mb[512]; toChar(msg, mb, 512);
        Date oldD(qOld.month(), qOld.day(), qOld.year());
        Date newD(qNew.month(), qNew.day(), qNew.year());
        sched.updateTaskDate(String(mb), oldD, newD);
        QMessageBox::information(this, "Success", "Date updated!");
        });

    // ?? ViewTasksPage sub-menu ????????????????????????????????????????????????
    connect(viewTasksPage->ui.btnBack, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_HOME);
        });
    connect(viewTasksPage->ui.btnViewAll, &QPushButton::clicked, this, [this] {
        Task buf[256];
        int n = sched.loadTasksInto(buf, 256);
        fillTable(viewAllPage->ui.tableWidget, buf, n);
        stack->setCurrentIndex(PAGE_VIEW_ALL);
        });
    connect(viewTasksPage->ui.btnViewDone, &QPushButton::clicked, this, [this] {
        Task buf[256];
        int n = sched.loadTasksInto(buf, 256, "Done");
        fillTable(viewDonePage->ui.tableWidget, buf, n);
        stack->setCurrentIndex(PAGE_VIEW_DONE);
        });
    connect(viewTasksPage->ui.btnViewToDo, &QPushButton::clicked, this, [this] {
        Task buf[256];
        int n = sched.loadTasksInto(buf, 256, "Todo");
        fillTable(viewTodoPage->ui.tableWidget, buf, n);
        stack->setCurrentIndex(PAGE_VIEW_TODO);
        });
    connect(viewTasksPage->ui.btnViewInProgress, &QPushButton::clicked, this, [this] {
        Task buf[256];
        int n = sched.loadTasksInto(buf, 256, "InProgress");
        fillTable(viewInProgressPage->ui.tableWidget, buf, n);
        stack->setCurrentIndex(PAGE_VIEW_INPROGRESS);
        });
    connect(viewTasksPage->ui.btnViewToday, &QPushButton::clicked, this, [this] {
        Task buf[256];
        Date today = Schedular::getCurrentDate();
        int n = sched.loadTasksInto(buf, 256, nullptr, &today);
        fillTable(viewTodayPage->ui.tableWidget, buf, n);
        stack->setCurrentIndex(PAGE_VIEW_TODAY);
        });
    connect(viewTasksPage->ui.btnViewSpecific, &QPushButton::clicked, this, [this] {
        stack->setCurrentIndex(PAGE_VIEW_SPECIFIC);
        });

    // View Specific — refresh table whenever the date picker changes
    connect(viewSpecificPage->ui.dateEdit, &QDateEdit::dateChanged,
        this, [this](const QDate& qd) {
            Task buf[256];
            Date d(qd.month(), qd.day(), qd.year());
            int n = sched.loadTasksInto(buf, 256, nullptr, &d);
            fillTable(viewSpecificPage->ui.tableWidget, buf, n);
        });

    // ?? Back buttons on all view pages ????????????????????????????????????????
    connect(viewAllPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewDonePage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewTodoPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewInProgressPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewTodayPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
    connect(viewSpecificPage->ui.btnBack, &QPushButton::clicked, this, [this] { stack->setCurrentIndex(PAGE_VIEW_TASKS); });
}