#ifndef VIEWDONEPAGE_H
#define VIEWDONEPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewdonepage;
}

class viewdonepage : public QWidget
{
    Q_OBJECT

public:
    explicit viewdonepage(QWidget *parent = nullptr);
    ~viewdonepage();
    QPushButton *btnBack;


private:
    Ui::viewdonepage *ui;
};

#endif // VIEWDONEPAGE_H
