#ifndef VIEWSPECIFICPAGE_H
#define VIEWSPECIFICPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewspecificpage;
}

class viewspecificpage : public QWidget
{
    Q_OBJECT

public:
    explicit viewspecificpage(QWidget *parent = nullptr);
    ~viewspecificpage();
    QPushButton *btnBack;


private:
    Ui::viewspecificpage *ui;
};

#endif // VIEWSPECIFICPAGE_H
