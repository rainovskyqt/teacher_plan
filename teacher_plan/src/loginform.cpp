#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_btn_enter_clicked()
{
    while(!authentication(ui->line_login->text(), ui->line_password->text())){
        QMessageBox::critical(this, tr("неверный логин"), tr("Не верный логин или пароль, проверте учетные данные!"));
    }

    emit enterToSystem();
}

bool LoginForm::authentication(QString login, QString password)
{
    return true;
}
