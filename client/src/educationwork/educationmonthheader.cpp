#include "educationmonthheader.h"
#include "ui_educationmonthheader.h"

#include "educationweekheader.h"
#include "settings.h"

EducationMonthHeader::EducationMonthHeader(Month::Months month, int startWeek, int weekCount, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationMonthHeader)
{
    ui->setupUi(this);

    ui->lbl_name->setText(Month().name(month));
    addWeeks(startWeek, weekCount);
}

EducationMonthHeader::~EducationMonthHeader()
{
    delete ui;
}

void EducationMonthHeader::addWeeks(int start, int count)
{
    for(int i = start; i < start + count; ++i){
        auto date = Settings::get().weekDate(i);
        auto week = new EducationWeekHeader(i, this);
        week->setStartDay(date.first);
        week->setEndDay(date.second);
        ui->hl_weeks->addWidget(week);
    }
}
