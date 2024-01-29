#include "totaltime.h"
#include "ui_totaltime.h"

TotalTime::TotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TotalTime)
{
    ui->setupUi(this);
}

TotalTime::~TotalTime()
{
    delete ui;
}
