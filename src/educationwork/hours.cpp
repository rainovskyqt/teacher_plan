#include "hours.h"

Hour::Hour(QObject *parent) : QObject(parent)
{
    m_id = 0;
    m_week = 0;
    m_plan = 0;
    m_fact = 0;
}

int Hour::id() const
{
    return m_id;
}

void Hour::setId(int newId)
{
    m_id = newId;
}

int Hour::week() const
{
    return m_week;
}

void Hour::setWeek(int newWeek)
{
    m_week = newWeek;
}

int Hour::plan() const
{
    return m_plan;
}

void Hour::setPlan(int newPlan)
{
    m_plan = newPlan;
}

int Hour::fact() const
{
    return m_fact;
}

void Hour::setFact(int newFact)
{
    m_fact = newFact;
}

//=============================TotalHour=============================
TotalHour::TotalHour(QObject *parent)
{

}
