#ifndef UPDATEDATEPAGE_H
#define UPDATEDATEPAGE_H

#include <QWidget>
#include<QPushButton>

namespace Ui {
class updatedatepage;
}

class updatedatepage : public QWidget
{
    Q_OBJECT

public:
    explicit updatedatepage(QWidget *parent = nullptr);
    ~updatedatepage();
    QPushButton *btnBack;
    QPushButton *btnUpdate;


private:
    Ui::updatedatepage *ui;
};

#endif // UPDATEDATEPAGE_H
