#include "educationheader.h"
#include "ui_educationheader.h"
#include "misc/month.h"

#include "QScrollBar"
#include "educationmonth.h"

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
        int weekCount = 4;
        ui->hl_months->addWidget(new EducationMonth((Month::Months)i, startWeek, weekCount, this));
        startWeek += weekCount;
    }
}
