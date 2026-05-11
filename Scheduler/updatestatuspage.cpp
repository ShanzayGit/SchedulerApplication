#include "updatestatuspage.h"
#include "ui_updatestatuspage.h"
#include <QFont>
updatestatuspage::updatestatuspage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::updatestatuspage)
{
    ui->setupUi(this);

    QFont globalFont("Segoe Script",9);
    this->setFont(globalFont);
    ui->comboBox->addItems({"Todo", "InProgress", "Done"});

    btnBack=ui->btnBack;
    btnUpdate=ui->btnUpdate;
}

updatestatuspage::~updatestatuspage()
{
    delete ui;
}
