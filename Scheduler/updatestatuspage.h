#ifndef UPDATESTATUSPAGE_H
#define UPDATESTATUSPAGE_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class updatestatuspage;
}

class updatestatuspage : public QWidget
{
    Q_OBJECT

public:
    explicit updatestatuspage(QWidget *parent = nullptr);
    ~updatestatuspage();

    QPushButton *btnBack;
    QPushButton *btnUpdate;

private:
    Ui::updatestatuspage *ui;
};

#endif // UPDATESTATUSPAGE_H
