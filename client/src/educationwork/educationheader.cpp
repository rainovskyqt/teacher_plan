#include "educationheader.h"
#include "ui_educationheader.h"
#include "misc/month.h"

#include "QScrollBar"
#include "educationmonthheader.h"
#include "settings.h"
#include <QDebug>

EducationHeader::EducationHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationHeader)
{
    ui->setupUi(this);
    addMonths();
}

EducationHeader::~EducationHeader()
{
    delete ui;
}

void EducationHeader::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void EducationHeader::addMonths()
{
    int startWeek = 1;
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other)
            i = Month::January;                //Если перешли за декабрь, ставим январь
        int weekCount = Settings::get().weekCount(static_cast<Month::Months>(i));
        ui->hl_months->addWidget(new EducationMonthHeader(static_cast<Month::Months>(i), startWeek, weekCount, this));
        startWeek += weekCount;
    }
}
