#include "header.h"
#include "ui_header.h"

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);
}

Header::~Header()
{
    delete ui;
}

void Header::on_btn_approvedCancel_clicked()
{
    ui->sw_approved->setCurrentIndex(1);
}


void Header::on_btn_toApprove_clicked()
{
    ui->sw_approved->setCurrentIndex(2);

}

