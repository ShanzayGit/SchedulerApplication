#include "viewtodaypage.h"
#include "ui_viewtodaypage.h"
#include<QFont>
viewtodaypage::viewtodaypage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewtodaypage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;

}

viewtodaypage::~viewtodaypage()
{
    delete ui;
}
