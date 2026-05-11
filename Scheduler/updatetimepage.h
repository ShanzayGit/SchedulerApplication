#ifndef UPDATETIMEPAGE_H
#define UPDATETIMEPAGE_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class updatetimepage;
}

class updatetimepage : public QWidget
{
    Q_OBJECT

public:
    explicit updatetimepage(QWidget *parent = nullptr);
    ~updatetimepage();

    QPushButton *btnBack;
    QPushButton *btnUpdate;

private:
    Ui::updatetimepage *ui;
};

#endif // UPDATETIMEPAGE_H
