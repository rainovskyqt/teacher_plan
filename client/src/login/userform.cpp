#include "userform.h"
#include "ui_userform.h"

UserForm::UserForm(QWidget *parent, User* user)
    : QDialog(parent)
    , ui(new Ui::UserForm)
{
    ui->setupUi(this);
    loadData();

    connect(ui->btn_register, &QPushButton::clicked, this, &UserForm::accept);
    connect(ui->btn_cancel, &QPushButton::clicked, this, &UserForm::reject);
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
        ui->line_rang->text(),
        ui->line_password->text()
        );
    user->addPost(ui->cb_department->currentData().toInt(), ui->cb_post->currentData().toInt());
    if(ui->cb_department_2->currentIndex() != 0)
        user->addPost(ui->cb_department_2->currentData().toInt(), ui->cb_post_2->currentData().toInt());

    return user;
}

void UserForm::loadData()
{
    auto database = Database::get();

    connect(database, &Database::dictionary, this, &UserForm::loadDictionary);
    database->requestDictionary(Database::Department);
    database->requestDictionary(Database::Post);
}

void UserForm::loadDictionary(Database::DictName dictName, QList<Dictionary *> dict)
{
    switch (dictName) {
    case Database::Department:
        foreach (auto row, dict) {
            ui->cb_department->addItem(row->name(), row->id());
            ui->cb_department_2->addItem(row->name(), row->id());
        }
        break;
    case Database::Post:
        foreach (auto row, dict) {
            ui->cb_post->addItem(row->name(), row->id());
            ui->cb_post_2->addItem(row->name(), row->id());
        }
        break;
    }
}
