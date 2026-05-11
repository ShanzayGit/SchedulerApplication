#ifndef UPDATEMESSAGEPAGE_H
#define UPDATEMESSAGEPAGE_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class updatemessagepage;
}

class updatemessagepage : public QWidget
{
    Q_OBJECT

public:
    explicit updatemessagepage(QWidget *parent = nullptr);
    ~updatemessagepage();

    QPushButton *btnBack;
    QPushButton *btnUpdate;

private:
    Ui::updatemessagepage *ui;
};

#endif // UPDATEMESSAGEPAGE_H
