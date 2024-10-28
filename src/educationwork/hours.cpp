#include "hours.h"

#include <misc/months.h>

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
TotalHour::TotalHour(QObject *parent) : QObject(parent)
{
}

void TotalHour::setHours(const QMap<int, Hour*> &newHours)
{
    m_hours.clear();
    m_hours = newHours;

    splitSemesters();
}

int TotalHour::firstPlane() const
{
    int count = 0;

    for(auto h : qAsConst(m_first))
        count += h->plan();

    return count;
}

int TotalHour::secondPlane() const
{
    int count = 0;

    for(auto h : qAsConst(m_second))
        count += h->plan();

    return count;
}

int TotalHour::firstFact() const
{
    int count = 0;

    for(auto h : qAsConst(m_first))
        count += h->fact();

    return count;
}

int TotalHour::secondFact() const
{
    int count = 0;

    for(auto h : qAsConst(m_second))
        count += h->fact();

    return count;
}

void TotalHour::splitSemesters()
{
    m_first.clear();
    m_second.clear();

    auto m = Months::get();
    auto hours = m_hours.values();

    for(Hour *h : hours){
        if(m->isFirstSemester(h->week())){
            m_first.append(h);
        } else {
            m_second.append(h);
        }
    }
}
