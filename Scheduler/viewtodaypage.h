#ifndef VIEWTODAYPAGE_H
#define VIEWTODAYPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewtodaypage;
}

class viewtodaypage : public QWidget
{
    Q_OBJECT

public:
    explicit viewtodaypage(QWidget *parent = nullptr);
    ~viewtodaypage();
    QPushButton *btnBack;


private:
    Ui::viewtodaypage *ui;
};

#endif // VIEWTODAYPAGE_H
