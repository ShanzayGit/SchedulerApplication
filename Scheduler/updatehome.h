#ifndef UPDATEHOME_H
#define UPDATEHOME_H

#include <QWidget>

namespace Ui {
class UpdateHome;
}

class UpdateHome : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateHome(QWidget *parent = nullptr);
    ~UpdateHome();

private:
    Ui::UpdateHome *ui;

signals:
    void backToMainHome(); // signal to notify MainWindow

};

#endif // UPDATEHOME_H
