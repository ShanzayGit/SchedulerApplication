#include "viewinprogresspage.h"
#include "ui_viewinprogresspage.h"
#include<QFont>
viewinprogresspage::viewinprogresspage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewinprogresspage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;

}

viewinprogresspage::~viewinprogresspage()
{
    delete ui;
}
