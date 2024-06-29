#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private:
    Ui::MainWindow *ui;

    enum Pages{
        Login,
        TotalTime
    };

    int m_userBaseId;
    int m_currentPlanId;

    bool authentication(QString login, QString password);
    void enterToSystem();

};
#endif // MAINWINDOW_H
