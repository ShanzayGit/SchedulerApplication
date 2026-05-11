#ifndef VIEWALLPAGE_H
#define VIEWALLPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class viewallpage;
}

class viewallpage : public QWidget
{
    Q_OBJECT

public:
    explicit viewallpage(QWidget *parent = nullptr);
    ~viewallpage();
    QPushButton *btnBack;

private:
    Ui::viewallpage *ui;
};

#endif // VIEWALLPAGE_H
