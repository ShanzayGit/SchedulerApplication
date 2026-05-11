#include "viewallpage.h"
#include "ui_viewallpage.h"
#include<QFont>
viewallpage::viewallpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewallpage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;
}

viewallpage::~viewallpage()
{
    delete ui;
}
