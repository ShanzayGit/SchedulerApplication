#include "addtaskspage.h"
#include "ui_addtaskspage.h"
#include<QFont>
AddTasksPage::AddTasksPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddTasksPage)
{
    ui->setupUi(this);
    btnBack = ui->btnBack;  // ✅ link to UI element

    // Or add all at once
    ui->comboBox->addItems({"Todo", "InProgress", "Done"});
    ui->comboBox->setEditable(false);
    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
}

AddTasksPage::~AddTasksPage()
{
    delete ui;
}
