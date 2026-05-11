#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    // Expose buttons so MainWindow can connect to them
    QPushButton *btnAddTask;
    QPushButton *btnUpdateTask;
    QPushButton *btnViewTasks;

private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
