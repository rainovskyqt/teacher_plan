#include "educationweek.h"
#include "ui_educationweek.h"

#include <QIntValidator>

EducationWeek::EducationWeek(EducationalHour *planHour, EducationalHour *factHour, bool readOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationWeek)
  ,m_number(planHour->week())
  ,m_planHour(planHour)
  ,m_factHour(factHour)
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

void EducationWeek::setTime(EducationalHour *hour)
{
    auto val = hour->value() ? QString::number(hour->value()) : "";
    if(hour->type() == EducationalHour::Plane){
        ui->line_plan->setText(val);
        m_planHour = hour;
        on_line_plan_textEdited(val);
    } else {
        ui->line_fact->setText(val);
        m_factHour = hour;
        on_line_fact_textEdited(val);
    }
}

void EducationWeek::clear()
{
    ui->line_plan->setText(0);
    on_line_plan_textEdited(0);
    ui->line_fact->setText(0);
    on_line_fact_textEdited(0);
}

void EducationWeek::on_line_plan_textEdited(const QString &arg1)
{
    m_planHour->setValue(arg1.toInt());
    emit hoursChanged(m_planHour);
}

void EducationWeek::on_line_fact_textEdited(const QString &arg1)
{
    m_factHour->setValue(arg1.toInt());
    emit hoursChanged(m_factHour);
}

