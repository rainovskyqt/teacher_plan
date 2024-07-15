#include "educationmonth.h"
#include "educationweek.h"
#include "ui_educationmonth.h"

EducationMonth::EducationMonth(Month::Months month, int startWeek, int weekCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationMonth)
{
    ui->setupUi(this);

    ui->lbl_name->setText(Month().name(month));
    addWeeks(startWeek, weekCount);
}

EducationMonth::~EducationMonth()
{
    delete ui;
}

void EducationMonth::addWeeks(int start, int count)
{
    for(int i = start; i < start + count; ++i){
        ui->hl_weeks->addWidget(new EducationWeek(i, this));
    }
}
