#include "educationalworkcomplite.h"
#include "ui_educationalworkcomplite.h"

EducationalWorkComplite::EducationalWorkComplite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationalWorkComplite)
{
    ui->setupUi(this);
}

EducationalWorkComplite::~EducationalWorkComplite()
{
    delete ui;
}

void EducationalWorkComplite::setYearHours(int hours)
{
    QString h = "часов";
    auto remainder = hours % 10;

    switch (remainder) {
    case 1:
        h = "час";
        break;
    case 2:
    case 3:
    case 4:
        h = "часа";
    }

    ui->lbl_yearHours->setText(QString::number(hours));
    ui->lbl_hourText->setText(h);
}
