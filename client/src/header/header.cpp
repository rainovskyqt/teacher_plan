#include "header.h"
#include "ui_header.h"

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

void Header::init(int userId)
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
    loadDictionary(ui->cb_department, Database::Department);
    loadDictionary(ui->cb_post, Database::Post);
}

void Header::loadDictionary(QComboBox *cb, Database::Dictionary dict)
{
    QMap<int, QString> departaments = Database::get()->dictionary(dict);
    for(QMap<int, QString>::iterator it = departaments.begin(); it != departaments.end(); ++it){
        cb->addItem(it.value(), it.key());
    }
}
