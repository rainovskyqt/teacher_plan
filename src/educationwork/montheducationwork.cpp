#include "montheducationwork.h"
#include "ui_montheducationwork.h"

MonthEducationWork::MonthEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonthEducationWork)
{
    ui->setupUi(this);
}

MonthEducationWork::~MonthEducationWork()
{
    delete ui;
}
