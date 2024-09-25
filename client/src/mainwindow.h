#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <database/models/teacherplan.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class User;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(User *user, QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void setPlanData(TeacherPlan *plan);
    void on_btn_create_clicked();

    void on_a_exit_triggered();

private:
    Ui::MainWindow *ui;

    enum Pages{
        Message,
        TotalTime
    };

    void setTypes();

    TeacherPlan *m_currentPlan;

    void checkUpdateComments(int userId);

};
#endif // MAINWINDOW_H
