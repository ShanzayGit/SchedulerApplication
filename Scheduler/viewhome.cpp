#include "viewhome.h"
#include "ui_viewhome.h"
#include"viewallpage.h"
#include"viewdonepage.h"
#include"viewinprogresspage.h"
#include"viewtodopage.h"
#include"viewspecificpage.h"
#include"viewtodaypage.h"
#include"viewtaskspage.h"

ViewHome::ViewHome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewHome)
{
    ui->setupUi(this);
    ViewTasksPage *viewtaskspage=new ViewTasksPage;
    viewallpage *viewAllPage = new viewallpage;
    viewdonepage *viewDonePage = new viewdonepage;
    viewinprogresspage *viewInProgressPage = new viewinprogresspage;
    viewspecificpage *viewSpecificPage = new viewspecificpage;
    viewtodaypage *viewTodayPage=new viewtodaypage;
    viewtodopage *viewTodoPage=new viewtodopage;

    ui->stackedWidget->addWidget(viewtaskspage);
    ui->stackedWidget->addWidget(viewAllPage); // index 1
    ui->stackedWidget->addWidget(viewTodoPage); // index 2
    ui->stackedWidget->addWidget(viewInProgressPage); // index 3
    ui->stackedWidget->addWidget(viewDonePage); // index 4
    ui->stackedWidget->addWidget(viewTodayPage); // index 5
    ui->stackedWidget->addWidget(viewSpecificPage); // index 6

    ui->stackedWidget->setCurrentIndex(0);

    // Buttons to switch
    connect(viewtaskspage->btnViewAll, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(viewtaskspage->btnViewTodo, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(viewtaskspage->btnViewInProgress, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(viewtaskspage->btnViewDone, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(4);
    });
    connect(viewtaskspage->btnViewToday, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(5);
    });
    connect(viewtaskspage->btnViewSpecific, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(6);
    });


    // Back buttons inside each subpage → return to UpdateHome menu
    connect(viewAllPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewTodoPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewSpecificPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewTodayPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewDonePage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewInProgressPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(viewtaskspage->btnBack, &QPushButton::clicked, this, [=]() {
        emit backToMainHome(); // tell MainWindow to go home
    });

}

ViewHome::~ViewHome()
{
    delete ui;
}
