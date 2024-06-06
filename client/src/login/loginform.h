#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "user.h"

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
    void enterToSystem(User*);

private slots:
    void on_btn_register_clicked();

private:
    Ui::LoginForm *ui;

};

#endif // LOGINFORM_H
