#include "plantime.h"

#define MAX_FULL_RATE_HOURS 1512
#define MAX_FULL_RATE_EDUCATIONAL_HOURS 900
#define ELEMENTS_COUNT 4

PlanTime::PlanTime(int orderNumber,QString name, int firstSemesterHours, int secondSemesterHours, int baseId,QObject *parent)
    : QObject{parent}
{
    m_orderNumber = orderNumber;
    m_name = name;
    m_firstSemesterHours = firstSemesterHours;
    m_secondSemesterHours = secondSemesterHours;
    m_baseId = baseId;
}

int PlanTime::maxHoursCount(WorkType type)
{
    switch (type) {
    case WorkType::Total:
        return MAX_FULL_RATE_HOURS;
    case WorkType::Educational:
        return MAX_FULL_RATE_EDUCATIONAL_HOURS;
    default:
        return 0;
    }
}

QString PlanTime::name() const
{
    return m_name;
}

int PlanTime::semesterHours(Semester semester) const
{
    if(semester == FirstSemester)
        return m_firstSemesterHours;
    else
        return m_secondSemesterHours;
}

void PlanTime::setSemesterHours(int semesterHours, Semester semester)
{
    if(semester == FirstSemester)
        m_firstSemesterHours = semesterHours;
    else
        m_secondSemesterHours = semesterHours;
}

QString PlanTime::romanNumeral()
{
    return toRomanNumeral(m_orderNumber);
}

QString PlanTime::toRomanNumeral(int numeral)
{
    switch (numeral) {
    case 1:
        return "I";
    case 2:
        return "II";
    case 3:
        return "III";
    case 4:
        return "IV";
    case 5:
        return "V";
    default:
        return "0";
    }
}
