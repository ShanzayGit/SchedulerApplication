#include "updatedatepage.h"
#include "ui_updatedatepage.h"
#include <QFont>
updatedatepage::updatedatepage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updatedatepage)
{
    ui->setupUi(this);
    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    btnBack=ui->btnBack;
    btnUpdate=ui->btnUpdate;
}

updatedatepage::~updatedatepage()
{
    delete ui;
}
