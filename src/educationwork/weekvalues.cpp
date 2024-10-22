#include "weekvalues.h"
#include "ui_weekvalues.h"

WeekValues::WeekValues(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekValues)
{
    ui->setupUi(this);

    connect(ui->line_plane, &ClearingLine::valueChanged, this, &WeekValues::updatetValue);
    connect(ui->line_fact, &ClearingLine::valueChanged, this, &WeekValues::updatetValue);
}

WeekValues::~WeekValues()
{
    delete ui;
}

void WeekValues::updatetValue()
{
    // emit valueUpdated(Hour(m_id,
    //                     m_week,
    //                     ui->line_plane->text().toInt(),
    //                     ui->line_fact->text().toInt()));
}

int WeekValues::week() const
{
    return m_week;
}

int WeekValues::planeValue() const
{
    return ui->line_plane->text().toInt();
}

int WeekValues::factValue() const
{
    return ui->line_fact->text().toInt();
}

void WeekValues::setWeekValues(Hour *hours)
{
    m_hours = hours;
    ui->line_plane->setNum(hours->plan());
    ui->line_fact->setNum(hours->fact());
}

void WeekValues::setWeek(int newWeek)
{
    m_week = newWeek;
}


