#include "header.h"
#include "ui_header.h"

#include <login/user.h>

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);
    this->setVisible(false);
}

Header::~Header()
{
    delete ui;
}

void Header::init()
{
    this->setVisible(true);

    loadDictionaries();
}

void Header::on_btn_approvedCancel_clicked()
{
    ui->sw_approved->setCurrentIndex(1);
}


void Header::on_btn_toApprove_clicked()
{
    ui->sw_approved->setCurrentIndex(2);

}

void Header::loadDictionaries()
{
    connect(Database::get(), &Database::dictionary, this, &Header::loadDictionary);
    Database::get()->requestDictionary(Database::Department);
    Database::get()->requestDictionary(Database::Post);
    Database::get()->requestStaff(User::get()->baseId());
}

void Header::loadDictionary(Database::Dictionary dictName, QMap<int, QString> dict)
{
    QComboBox *cb;
    switch (dictName) {
    case Database::Department: cb = ui->cb_department; break;
    case Database::Post: cb = ui->cb_post; break;
    }

    for(QMap<int, QString>::iterator it = dict.begin(); it != dict.end(); ++it){
        cb->addItem(it.value(), it.key());
    }
}

