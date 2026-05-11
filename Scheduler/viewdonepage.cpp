#include "viewdonepage.h"
#include "ui_viewdonepage.h"
#include<QFont>
viewdonepage::viewdonepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::viewdonepage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->tableWidget->setHorizontalHeaderLabels({"Date", "Time", "Message", "Status"});
    ui->tableWidget->setAlternatingRowColors(true);
    btnBack=ui->btnBack;

}

viewdonepage::~viewdonepage()
{
    delete ui;
}
