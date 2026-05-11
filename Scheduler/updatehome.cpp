#include "updatehome.h"
#include "ui_updatehome.h"
#include "updatetaskspage.h"
#include"updatedatepage.h"
#include"updatetimepage.h"
#include"updatestatusPage.h"
#include"updatemessagepage.h"


UpdateHome::UpdateHome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UpdateHome)
{
    ui->setupUi(this);


    // Create 4 subpages
    UpdateTasksPage *updatetasksPage=new UpdateTasksPage;
    updatemessagepage *updateMessagePage = new updatemessagepage;
    updatedatepage *updateDatePage = new updatedatepage;
    updatetimepage *updateTimePage = new updatetimepage;
    updatestatuspage *updateStatusPage = new updatestatuspage;

    ui->stackedWidget->addWidget(updatetasksPage);
    ui->stackedWidget->addWidget(updateMessagePage); // index 1
    ui->stackedWidget->addWidget(updateTimePage); // index 2
    ui->stackedWidget->addWidget(updateStatusPage); // index 3
    ui->stackedWidget->addWidget(updateDatePage); // index 4

    ui->stackedWidget->setCurrentIndex(0);

    // Buttons to switch
    connect(updatetasksPage->btnUpdateDate, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(4);
    });
    connect(updatetasksPage->btnUpdateTime, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(2);
    });
    connect(updatetasksPage->btnUpdateMsg, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(updatetasksPage->btnUpdateStatus, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(3);
    });

    // Back buttons inside each subpage → return to UpdateHome menu
    connect(updateStatusPage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0); // show UpdateHome menu page
    });
    connect(updateDatePage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(updateTimePage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(updateMessagePage->btnBack, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(updatetasksPage->btnBack, &QPushButton::clicked, this, [=]() {
        emit backToMainHome(); // tell MainWindow to go home
    });

}

UpdateHome::~UpdateHome()
{
    delete ui;
}
