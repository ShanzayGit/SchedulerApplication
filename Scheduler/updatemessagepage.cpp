#include "updatemessagepage.h"
#include "ui_updatemessagepage.h"
#include<QFont>
updatemessagepage::updatemessagepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updatemessagepage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);

    btnBack=ui->btnBack;
    btnUpdate=ui->btnUpdate;
}

updatemessagepage::~updatemessagepage()
{
    delete ui;
}
