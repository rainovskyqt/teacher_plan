#include "loginform.h"
#include "ui_loginform.h"

#include <QMessageBox>
#include <QDebug>

#include "database/database.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);

#ifdef QT_DEBUG
    ui->line_login->setText("admin");
    ui->line_password->setText("admin");
#endif

    connect(ui->btn_enter, &QPushButton::clicked, this, [&](){
        Database::instance()->login(ui->line_login->text(), ui->line_password->text());
    });

    connect(Database::instance(), &Database::logged, this, [&](int id){
        if(id){
            emit enterToSystem(id);
        } else {
            QMessageBox::critical(this, tr("Не верные данные"), tr("Не верные учетные данные"));
            return;
        }
    });

}

LoginForm::~LoginForm()
{
    delete ui;
}
