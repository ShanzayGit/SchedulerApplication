#include "updatetaskspage.h"
#include "ui_updatetaskspage.h"
#include<QFont>
UpdateTasksPage::UpdateTasksPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UpdateTasksPage)
{
    ui->setupUi(this);

    btnBack = ui->btnBack;  // ✅ link to UI element
    btnUpdateMsg =ui->btnUpdateMsg;
    btnUpdateTime =ui->btnUpdateTime;
    btnUpdateDate =ui->btnUpdateDate;
    btnUpdateStatus=ui->btnUpdateStatus;

    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);
    ui->plainTextEdit_4->setReadOnly(true);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);

}

UpdateTasksPage::~UpdateTasksPage()
{
    delete ui;
}
