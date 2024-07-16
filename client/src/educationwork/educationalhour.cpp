#include "educationalhour.h"

EducationalHour::EducationalHour(int baseId, int planeWorkId, int week,
                                 int value, EducationalHour::HourType type, QObject *parent)
    : QObject{parent}
{
    m_baseId = baseId;
    m_planeWorkId = planeWorkId;
    m_week = week;
    m_value = value;
    m_type = type;
}

EducationalHour::EducationalHour(EducationalHour::HourType type, QObject *parent) : QObject{parent}
{
    m_type = type;
    m_baseId = 0;
    m_planeWorkId = 0;
    m_week = 0;
    m_value = 0;
}

int EducationalHour::baseId() const
{
    return m_baseId;
}

int EducationalHour::planeWorkId() const
{
    return m_planeWorkId;
}

int EducationalHour::week() const
{
    return m_week;
}

int EducationalHour::value() const
{
    return m_value;
}

void EducationalHour::setValue(int newValue)
{
    m_value = newValue;
}

EducationalHour::HourType EducationalHour::type() const
{
    return m_type;
}
