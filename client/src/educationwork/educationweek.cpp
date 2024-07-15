#include "educationweek.h"
#include "ui_educationweek.h"

EducationWeek::EducationWeek(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWeek)
{
    ui->setupUi(this);
    ui->lbl_number->setText(QString::number(number));
}

EducationWeek::~EducationWeek()
{
    delete ui;
}

int EducationWeek::startDay()
{
    return ui->lbl_start->text().toInt();
}

void EducationWeek::setStartDay(int start)
{
    ui->lbl_start->setText(QString::number(start));
}

int EducationWeek::endDay()
{
    return ui->lbl_end->text().toInt();
}

void EducationWeek::setEndDay(int end)
{
    ui->lbl_end->setText(QString::number(end));
}

int EducationWeek::weekNumber()
{
    return ui->lbl_number->text().toInt();
}

void EducationWeek::setWeekNumber(int number)
{
    ui->lbl_number->setText(QString::number(number));
}
