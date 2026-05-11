#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    // Assign UI elements to public pointers
    btnAddTask = ui->btnAddTask;
    btnUpdateTask = ui->btnUpdateTask;
    btnViewTasks = ui->btnViewTasks;
    ui->addTask->setReadOnly(true);
    ui->updateTask->setReadOnly(true);
    ui->viewTask->setReadOnly(true);
}

HomePage::~HomePage()
{
    delete ui;
}
