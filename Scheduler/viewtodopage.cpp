#include "viewtodopage.h"
#include "ui_viewtodopage.h"
#include<QFont>
viewtodopage::viewtodopage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewtodopage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;

}


viewtodopage::~viewtodopage()
{
    delete ui;
}
