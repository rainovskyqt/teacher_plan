#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>

#include "database/database.h"
#include "login/userform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);

#ifdef QT_DEBUG
    ui->line_login->setText("teacher");
    ui->line_password->setText("myPassword");
#endif

    connect(ui->btn_enter, &QPushButton::clicked, this, [&](){
        User *user = Database::get()->login(ui->line_login->text(), ui->line_password->text());
        emit enterToSystem(user);
    });

    // connect(Database::get(), &Database::connectionError, this, [&](QString error){
    //     QMessageBox::critical(this, tr("Ошибка подклчючени"), error);
    // });
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_btn_register_clicked()
{
    UserForm *form = new UserForm(this);
    if(form->exec() == QDialog::Rejected)
        return;

    auto user = form->newUser();
    Database::get()->addUser(user);
    \
    form->deleteLater();
}

