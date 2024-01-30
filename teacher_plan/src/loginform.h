#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

signals:
    void enterToSystem();

private slots:
    void on_btn_enter_clicked();

private:
    Ui::LoginForm *ui;

    bool authentication(QString login, QString password);
};

#endif // LOGINFORM_H
