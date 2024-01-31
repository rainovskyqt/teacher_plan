#include "plantime.h"

#define MAX__FULL_RATE_HOURS 1512
#define ELEMENTS_COUNT 4

PlanTime::PlanTime(QString romanNumeral, QString name, int firstSemesterHours, int secondSemesterHours, int baseId,QObject *parent)
    : QObject{parent}
{
    m_romanNumeral = romanNumeral;
    m_name = name;
    m_firstSemesterHours = firstSemesterHours;
    m_secondSemesterHours = secondSemesterHours;
    m_baseId = baseId;
}

int PlanTime::maxHoursCount(double rate)
{
    return MAX__FULL_RATE_HOURS;
}

int PlanTime::elementsCount()
{
    return ELEMENTS_COUNT;
}

QString PlanTime::romanNumeral() const
{
    return m_romanNumeral;
}

void PlanTime::setRomanNumeral(const QString &newRomanNumeral)
{
    m_romanNumeral = newRomanNumeral;
}

QString PlanTime::name() const
{
    return m_name;
}

void PlanTime::setName(const QString &newName)
{
    m_name = newName;
}

int PlanTime::firstSemesterHours() const
{
    return m_firstSemesterHours;
}

void PlanTime::setFirstSemesterHours(int newFirstSemesterHours)
{
    m_firstSemesterHours = newFirstSemesterHours;
}

int PlanTime::secondSemesterHours() const
{
    return m_secondSemesterHours;
}

void PlanTime::setSecondSemesterHours(int newSecondSemesterHours)
{
    m_secondSemesterHours = newSecondSemesterHours;
}
