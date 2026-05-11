#ifndef VIEWINPROGRESSPAGE_H
#define VIEWINPROGRESSPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewinprogresspage;
}

class viewinprogresspage : public QWidget
{
    Q_OBJECT

public:
    explicit viewinprogresspage(QWidget *parent = nullptr);
    ~viewinprogresspage();
    QPushButton *btnBack;


private:
    Ui::viewinprogresspage *ui;
};

#endif // VIEWINPROGRESSPAGE_H
