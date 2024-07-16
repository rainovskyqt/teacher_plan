#include "educationweekheader.h"
#include "ui_educationweekheader.h"

EducationWeekHeader::EducationWeekHeader(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWeekHeader)
{
    ui->setupUi(this);

    ui->lbl_number->setText(QString::number(number));
}

EducationWeekHeader::~EducationWeekHeader()
{
    delete ui;
}

int EducationWeekHeader::startDay()
{
    return ui->lbl_start->text().toInt();
}

void EducationWeekHeader::setStartDay(int start)
{
    ui->lbl_start->setText(QString::number(start));
}

int EducationWeekHeader::endDay()
{
    return ui->lbl_end->text().toInt();
}

void EducationWeekHeader::setEndDay(int end)
{
    ui->lbl_end->setText(QString::number(end));
}

int EducationWeekHeader::weekNumber()
{
    return ui->lbl_number->text().toInt();
}
