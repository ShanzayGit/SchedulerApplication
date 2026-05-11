#ifndef VIEWHOME_H
#define VIEWHOME_H

#include <QWidget>

namespace Ui {
class ViewHome;
}

class ViewHome : public QWidget
{
    Q_OBJECT

public:
    explicit ViewHome(QWidget *parent = nullptr);
    ~ViewHome();

private:
    Ui::ViewHome *ui;

signals:
    void backToMainHome(); // signal to notify MainWindow

};

#endif // VIEWHOME_H
