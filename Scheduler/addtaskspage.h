#ifndef ADDTASKSPAGE_H
#define ADDTASKSPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class AddTasksPage;
}

class AddTasksPage : public QWidget
{
    Q_OBJECT

public:
    explicit AddTasksPage(QWidget *parent = nullptr);
    ~AddTasksPage();

    QPushButton *btnBack;  // ✅ expose Back button

private:
    Ui::AddTasksPage *ui;
};

#endif // ADDTASKSPAGE_H
