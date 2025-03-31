#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <database/models/teacherplan.h>

#include <print/datafiles/printcomplite.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class User;
class PrintTotalData;

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
    void on_action_print_triggered();

    void setTotalTime(PrintTotalData *total);
    void setCompliteTime(PrintComplite *c);

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
