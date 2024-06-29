#include "plantime.h"
#include "teacherplan.h"
#include <QJsonDocument>
#include <QPair>

#define MAX_FULL_RATE_HOURS 1512
#define MAX_FULL_RATE_EDUCATIONAL_HOURS 900
#define ELEMENTS_COUNT 4

PlanTime::PlanTime(int workType, QString name, int firstSemesterHours, int secondSemesterHours,
                   int baseId, int orderPlace, QObject *parent)
    : QObject{parent}
{
    m_workType = workType;
    m_name = name;
    m_firstSemesterHours = firstSemesterHours;
    m_secondSemesterHours = secondSemesterHours;
    m_baseId = baseId;
    m_orderPlace = orderPlace;
    if(parent){
        auto teacherPlan = qobject_cast<TeacherPlan*>(parent);
        if(teacherPlan)
            m_planId = teacherPlan->baseId();
    } else {
        m_planId = 0;
    }
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

QString PlanTime::romanNumeral(int number)
{
    return toRomanNumeral(number);
}

int PlanTime::workType() const
{
    return m_workType;
}

void PlanTime::setWorkType(int newWorkType)
{
    m_workType = newWorkType;
}

int PlanTime::baseId() const
{
    return m_baseId;
}

void PlanTime::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
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
