#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>

#include "database/database.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);

#ifdef QT_DEBUG
    ui->line_login->setText("teacher");
    ui->line_password->setText("teacher");
#endif

    connect(ui->btn_enter, &QPushButton::clicked, this, [&](){
        Database::get()->login(ui->line_login->text(), ui->line_password->text());
    });

    connect(Database::get(), &Database::logged,
            this, [&](int base_id, QString token, QString refreshToken){
        if(base_id){
            emit enterToSystem(base_id, token, refreshToken);
        } else {
            QMessageBox::critical(this, tr("Не верные данные"), tr("Не верные учетные данные"));
            return;
        }
    });

    connect(Database::get(), &Database::connectionError, this, [&](QString error){
        QMessageBox::critical(this, tr("Ошибка подклчючени"), error);
    });
}

LoginForm::~LoginForm()
{
    delete ui;
}
