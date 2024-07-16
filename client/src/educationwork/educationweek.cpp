#include "educationweek.h"
#include "ui_educationweek.h"

#include <QIntValidator>

EducationWeek::EducationWeek(int number, bool readOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWeek),
    m_number(number)
{
    ui->setupUi(this);
    ui->line_plan->setValidator(new QIntValidator(0, 1000, this));
    ui->line_fact->setValidator(new QIntValidator(0, 1000, this));
    ui->line_fact->setReadOnly(readOnly);
    ui->line_plan->setReadOnly(readOnly);
}

EducationWeek::~EducationWeek()
{
    delete ui;
}

int EducationWeek::number() const
{
    return m_number;
}

int EducationWeek::getTime(EducationalHour::HourType type)
{
    if(type == EducationalHour::Plane)
        return ui->line_plan->text().toInt();
    else
        return ui->line_fact->text().toInt();
}

void EducationWeek::setTime(EducationalHour::HourType type, int value)
{
    auto val = QString::number(value);
    if(type == EducationalHour::Plane){
        ui->line_plan->setText(val);
        on_line_plan_textEdited(val);
    } else {
        ui->line_fact->setText(val);
        on_line_fact_textEdited(val);
    }
}

void EducationWeek::on_line_plan_textEdited(const QString &arg1)
{
    emit hoursChanged(EducationalHour::Plane, m_number, arg1.toInt());
}

void EducationWeek::on_line_fact_textEdited(const QString &arg1)
{
    emit hoursChanged(EducationalHour::Factical, m_number, arg1.toInt());
}

