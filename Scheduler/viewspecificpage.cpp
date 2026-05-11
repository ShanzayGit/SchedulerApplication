#include "viewspecificpage.h"
#include "ui_viewspecificpage.h"
#include<QFont>
viewspecificpage::viewspecificpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewspecificpage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;

}

viewspecificpage::~viewspecificpage()
{
    delete ui;
}
