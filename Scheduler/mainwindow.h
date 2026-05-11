#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

// Backend
#include "Scheduler.h"

// Forward declare all page widgets
class HomePage;
class AddTasksPage;
class UpdateTasksPage;
class ViewTasksPage;
class updatedatepage;
class updatemessagepage;
class updatestatuspage;
class updatetimepage;
class viewallpage;
class viewdonepage;
class viewinprogresspage;
class viewspecificpage;
class viewtodaypage;
class viewtodopage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QStackedWidget* stack;

    Schedular          sched;   // ? member, not static local — lambdas can capture this

    // Pages
    HomePage* homePage;
    AddTasksPage* addTasksPage;
    UpdateTasksPage* updateTasksPage;
    ViewTasksPage* viewTasksPage;
    updatedatepage* updateDatePage;
    updatemessagepage* updateMessagePage;
    updatestatuspage* updateStatusPage;
    updatetimepage* updateTimePage;
    viewallpage* viewAllPage;
    viewdonepage* viewDonePage;
    viewinprogresspage* viewInProgressPage;
    viewspecificpage* viewSpecificPage;
    viewtodaypage* viewTodayPage;
    viewtodopage* viewTodoPage;

    void setupPages();
    void connectSignals();

    enum Pages {
        PAGE_HOME = 0,
        PAGE_ADD_TASK,
        PAGE_UPDATE_TASKS,
        PAGE_VIEW_TASKS,
        PAGE_UPDATE_DATE,
        PAGE_UPDATE_MSG,
        PAGE_UPDATE_STATUS,
        PAGE_UPDATE_TIME,
        PAGE_VIEW_ALL,
        PAGE_VIEW_DONE,
        PAGE_VIEW_INPROGRESS,
        PAGE_VIEW_SPECIFIC,
        PAGE_VIEW_TODAY,
        PAGE_VIEW_TODO
    };
};

#endif // MAINWINDOW_H