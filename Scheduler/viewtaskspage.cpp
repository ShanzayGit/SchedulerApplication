#include "viewtaskspage.h"
#include "ui_viewtaskspage.h"
#include<QFont>
ViewTasksPage::ViewTasksPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ViewTasksPage)
{
    ui->setupUi(this);

    btnBack = ui->btnBack;  // ✅ link to UI element
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);
    ui->plainTextEdit_4->setReadOnly(true);
    ui->plainTextEdit_5->setReadOnly(true);
    ui->plainTextEdit_6->setReadOnly(true);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    btnBack=ui->btnBack;
    btnViewAll=ui->btnViewAll;
    btnViewDone=ui->btnViewDone;
    btnViewInProgress=ui->btnViewInProgress;
    btnViewSpecific=ui->btnViewSpecific;
    btnViewToday=ui->btnViewToday;
    btnViewTodo=ui->btnViewToDo;
}

ViewTasksPage::~ViewTasksPage()
{
    delete ui;
}
