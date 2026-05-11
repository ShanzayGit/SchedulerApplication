#include "updatetimepage.h"
#include "ui_updatetimepage.h"
#include<QFont>
updatetimepage::updatetimepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updatetimepage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);

    btnBack=ui->btnBack;
    btnUpdate=ui->btnUpdate;
}

updatetimepage::~updatetimepage()
{
    delete ui;
}
