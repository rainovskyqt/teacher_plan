#include "monthheader.h"
#include "ui_monthheader.h"

MonthHeader::MonthHeader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonthHeader)
{
    ui->setupUi(this);
}

MonthHeader::~MonthHeader()
{
    delete ui;
}
