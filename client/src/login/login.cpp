#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "userform.h"
#include "database/database.h"

#include <QButtonGroup>
#include <QMessageBox>
#include <mainwindow.h>
#include "settings.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &Login::login);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &Login::close);
#ifdef QT_DEBUG
    ui->line_login->setText("teacher");
    ui->line_password->setText("myPassword");
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
    User *user = Database::get()->login(ui->line_login->text(), ui->line_password->text());

    if(!user->baseId()){
        QMessageBox::critical(this, "Ошибка аутинтефикации", "Введены неверные логин и пароль");
        delete user;
    } else {
        Settings::get().setLastName(ui->line_login->text());
        MainWindow *w = new MainWindow(user);
        w->show();
        close();
    }
}

void Login::on_btn_register_clicked()
{
    UserForm *user = new UserForm(this);
    user->show();
}

