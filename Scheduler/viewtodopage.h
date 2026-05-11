#ifndef VIEWTODOPAGE_H
#define VIEWTODOPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewtodopage;
}

class viewtodopage : public QWidget
{
    Q_OBJECT

public:
    explicit viewtodopage(QWidget *parent = nullptr);
    ~viewtodopage();
    QPushButton *btnBack;


private:
    Ui::viewtodopage *ui;
};

#endif // VIEWTODOPAGE_H
