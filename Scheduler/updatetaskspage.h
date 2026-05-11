#ifndef UPDATETASKSPAGE_H
#define UPDATETASKSPAGE_H

#include <QWidget>
#include<QPushButton>
namespace Ui {
class UpdateTasksPage;
}

class UpdateTasksPage : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateTasksPage(QWidget *parent = nullptr);
    ~UpdateTasksPage();

    QPushButton *btnBack;  // ✅ expose Back button
    QPushButton *btnUpdateMsg;
    QPushButton *btnUpdateTime;
    QPushButton *btnUpdateDate;
    QPushButton *btnUpdateStatus;


private:
    Ui::UpdateTasksPage *ui;
};

#endif // UPDATETASKSPAGE_H
