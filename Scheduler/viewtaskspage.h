#ifndef VIEWTASKSPAGE_H
#define VIEWTASKSPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class ViewTasksPage;
}

class ViewTasksPage : public QWidget
{
    Q_OBJECT

public:
    explicit ViewTasksPage(QWidget *parent = nullptr);
    ~ViewTasksPage();

    QPushButton *btnBack;  // ✅ expose Back button
    QPushButton *btnViewInProgress;
    QPushButton *btnViewAll;
    QPushButton *btnViewSpecific;
    QPushButton *btnViewTodo;
    QPushButton *btnViewDone;
    QPushButton *btnViewToday;


private:
    Ui::ViewTasksPage *ui;
};

#endif // VIEWTASKSPAGE_H
