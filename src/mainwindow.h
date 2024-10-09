#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// #include <database/models/teacherplan.h>

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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent *e) override;

private slots:
    void getPlans(int staffId);
    // void setPlanData(TeacherPlan *plan);
    // void on_btn_create_clicked();

    // void on_a_exit_triggered();

private:
    Ui::MainWindow *ui;

    enum Pages{
        Message,
        TotalTime
    };

    int m_staffId;

    void init();
    void setTypes();
    void loadSpliterState();
    void saveSpliterState();
    void initFacultyPanel();
    void initConnections();
    void checkUpdateComments();

    // TeacherPlan *m_currentPlan;


};
#endif // MAINWINDOW_H
