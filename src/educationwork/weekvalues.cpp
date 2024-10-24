#include "weekvalues.h"
#include "ui_weekvalues.h"

WeekValues::WeekValues(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekValues)
{
    ui->setupUi(this);

    connect(ui->line_plane, &ClearingLine::valueChanged, this, [this]{
        m_hours->setPlan(ui->line_plane->text().toInt());
        emit valueUpdated(m_week);
    });

    connect(ui->line_fact, &ClearingLine::valueChanged, this, [this]{
        m_hours->setFact(ui->line_fact->text().toInt());
        emit valueUpdated(m_week);
    });
}

WeekValues::~WeekValues()
{
    delete ui;
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

void WeekValues::setPlaneReadOnly(bool readOnly)
{
    ui->line_plane->setReadOnly(readOnly);
}

void WeekValues::setFactReadOnly(bool readOnly)
{
    ui->line_fact->setReadOnly(readOnly);
}

void WeekValues::setWeekValues(Hour *hours)
{
    m_hours = hours;
    ui->line_plane->setNum(hours->plan());
    ui->line_fact->setNum(hours->fact());
    m_hours->setWeek(m_week);
}

void WeekValues::setWeek(int newWeek)
{
    m_week = newWeek;
}


