#include "educationalfooter.h"
#include "educationmonth.h"
#include "ui_educationalfooter.h"
#include <QScrollBar>
#include <misc/month.h>
#include "settings.h"

EducationalFooter::EducationalFooter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EducationalFooter)
{
    ui->setupUi(this);
    addMonths();
}

EducationalFooter::~EducationalFooter()
{
    delete ui;
}

void EducationalFooter::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void EducationalFooter::setValue(EducationalHour::HourType type, int week, int value)
{
    auto months = this->findChildren<EducationMonth*>();

    for(auto m: months){
        m->setValue(type, week, value);
    }
    countHours(type);
}


void EducationalFooter::addMonths()
{
    int startWeek = 1;
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other)
            i = Month::January;                //Если перешли за декабрь, ставим январь
        int weekCount = Settings::get().weekCount((Month::Months)i);
        auto month = new EducationMonth(startWeek, weekCount, true, this);
        ui->hl_months->addWidget(month);
        startWeek += weekCount;
    }
}

void EducationalFooter::countHours(EducationalHour::HourType type)
{
    int firstCount = 0;
    int secontCount = 0;
    auto month = this->findChildren<EducationMonth*>();
    for(auto m: month){
        if(m->isFirstSemester())
            firstCount += m->getTime(type);
        else
            secontCount += m->getTime(type);
    }

    if(type == EducationalHour::Plane){
        ui->lbl_firstPlan->setText(QString::number(firstCount));
        emit firstPlaneChanget(firstCount);
        ui->lbl_secondPlan->setText(QString::number(secontCount));
        emit secondPlaneChanget(secontCount);
        ui->lbl_yearPlan->setText(QString::number(firstCount + secontCount));
    } else {
        ui->lbl_firstFact->setText(QString::number(firstCount));
        emit firstFacticalChanget(firstCount);
        ui->lbl_secondFact->setText(QString::number(secontCount));
        emit secondFacticalChanget(secontCount);
        ui->lbl_yearFact->setText(QString::number(firstCount + secontCount));
    }
}
