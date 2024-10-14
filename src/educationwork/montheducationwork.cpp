#include "montheducationwork.h"
#include "ui_montheducationwork.h"
#include "weekeducationwork.h"

MonthEducationWork::MonthEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonthEducationWork)
{
    ui->setupUi(this);

    for(int i = 0; i < 5; ++i){
        ui->hl_weeks->addWidget(new WeekEducationWork(this));
    }
}

MonthEducationWork::~MonthEducationWork()
{
    delete ui;
}
