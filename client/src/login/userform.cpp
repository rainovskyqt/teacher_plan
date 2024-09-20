#include "userform.h"
#include "ui_userform.h"

#include <database/adapters/dictionaryadapter.h>

UserForm::UserForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserForm)
{
    ui->setupUi(this);
    loadData();

    connect(ui->btn_register, &QPushButton::clicked, this, [this] {
        Database::get()->addUser(newUser());
        this->close();
    });
    connect(ui->btn_cancel, &QPushButton::clicked, this, &UserForm::reject);

    ui->label_8->setVisible(false);
    ui->cb_rang->setVisible(false);
}

UserForm::~UserForm()
{
    delete ui;
}

User *UserForm::newUser()
{
    User *user = new User();
    user->userData()->setData(
        ui->line_login->text(),
        ui->line_surname->text(),
        ui->line_name->text(),
        ui->line_middleName->text(),
        ui->cb_rang->currentText(),
        ui->cb_rang->currentData().toInt(),
        ui->line_password->text()
        );
    user->addPost(user->baseId(), ui->cb_department->currentData().toInt(), ui->cb_post->currentData().toInt(), true);
    if(ui->cb_department_2->currentIndex() != 0)
        user->addPost(user->baseId(), ui->cb_department_2->currentData().toInt(), ui->cb_post_2->currentData().toInt(), false);

    return user;
}

void UserForm::loadData()
{
    DictionaryAdapter::setDictionary(ui->cb_rang, Database::Rang);
    DictionaryAdapter::setDictionary(ui->cb_department, Database::Department);
    DictionaryAdapter::setDictionary(ui->cb_post, Database::Post);

    DictionaryAdapter::setDictionary(ui->cb_department_2, Database::Department);
    DictionaryAdapter::setDictionary(ui->cb_post_2, Database::Post);

}
