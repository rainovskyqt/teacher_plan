#include "login.h"
#include "ui_login.h"
#include "user.h"
#include "database/database.h"

#include <QButtonGroup>
#include <QMessageBox>
#include <mainwindow.h>

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
    } else {
        MainWindow *w = new MainWindow(user);
        w->show();
        close();
    }
}
