#include "login.h"
#include "ui_login.h"

#include <QButtonGroup>
#include <QMessageBox>
#include <QCryptographicHash>

#include "userform.h"
#include "database/database.h"
#include <mainwindow.h>
#include "settings.h"
#include <user/usermanager.h>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &Login::login);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &Login::close);

#ifdef QT_DEBUG
    ui->line_login->setText("temp");
    ui->line_password->setText("temp");
#else
    ui->line_login->setText(Settings::get().lastName());
#endif
}

Login::~Login()
{
    delete ui;
}

void Login::login()
{
    auto user = UserManager::get();
    bool login = user->login(ui->line_login->text(), encodePassword(ui->line_password->text()));

    if(!login){
        QMessageBox::critical(this, "Ошибка аутинтефикации", "Введены неверные логин и пароль.");
    } else {
        Settings::get().setLastName(ui->line_login->text());
        MainWindow *w = new MainWindow();
        w->show();
        close();
    }
}

const QString Login::encodePassword(const QString &password) const
{
    return QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
}

void Login::on_btn_register_clicked()
{
    UserForm *user = new UserForm(this);
    user->show();
}

