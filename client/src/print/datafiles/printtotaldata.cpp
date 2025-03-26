#include "printtotaldata.h"

PrintTotalData::PrintTotalData(QObject *parent)
    : PrintData{parent}
{

}

QString PrintTotalData::rate() const
{
    return m_rate;
}

void PrintTotalData::setRate(const QString &newRate)
{
    m_rate = newRate;
}

void PrintTotalData::setTime(WorkType type, PlanTime::Semester semester, int val)
{
    if(semester == PlanTime::FirstSemester)
        m_times[type].first = val;
    else
        m_times[type].second = val;
}

int PrintTotalData::getTime(WorkType type, PlanTime::Semester semester)
{
    if(semester == PlanTime::FirstSemester)
        return m_times[type].first ;
    else
        return  m_times[type].second;
}
