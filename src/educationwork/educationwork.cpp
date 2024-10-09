#include "educationwork.h"

Hour::Hour(int id, int week, int type, int value, QObject *parent) :
    QObject(parent)
    , m_id{id}
    , m_week{week}
    , m_type{type}
    , m_value{value}
{}

int Hour::id() const
{
    return m_id;
}

int Hour::week() const
{
    return m_week;
}

int Hour::type() const
{
    return m_type;
}

int Hour::value() const
{
    return m_value;
}

void Hour::setValue(int newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
}

EducationWork::EducationWork(int id, int discipline, int course, int workForm, int groupCount,
                             const QString &comments, int orderPlace, const QString &hours, QObject *parent)
    : QObject(parent)
{
    m_id = id;
    m_disciplineId = discipline;
    m_courseId = course;
    m_workFormId = workForm;
    m_groupCount = groupCount;
    m_comments = comments;
    m_orderPalce = orderPlace;
    m_hours = splitHours(hours);
}

QHash<int, Hour*> EducationWork::splitHours(const QString &hoursString)
{
    using HF = Hour::HourFields;
    QHash<int, Hour*> hours;
    QStringList splittedHours = hoursString.split(";", Qt::SkipEmptyParts);
    for(const QString &hourRow : qAsConst(splittedHours)){
        QStringList h = hourRow.split(",");
        hours.insert(h.at(HF::HourWeek).toInt(),
                     new Hour(h.at(HF::HourId).toInt(),
                          h.at(HF::HourWeek).toInt(),
                          h.at(HF::HourType).toInt(),
                          h.at(HF::HourValue).toInt(),
                          this
                          ));
    }
    return hours;
}

int EducationWork::id() const
{
    return m_id;
}

int EducationWork::disciplineId() const
{
    return m_disciplineId;
}

int EducationWork::courseId() const
{
    return m_courseId;
}

int EducationWork::workFormId() const
{
    return m_workFormId;
}

int EducationWork::groupCount() const
{
    return m_groupCount;
}

QString EducationWork::comments() const
{
    return m_comments;
}

int EducationWork::orderPalce() const
{
    return m_orderPalce;
}

QHash<int, Hour *> EducationWork::hours() const
{
    return m_hours;
}

void EducationWork::setDisciplineId(int newDisciplineId)
{
    m_disciplineId = newDisciplineId;
}

void EducationWork::setCourseId(int newCourseId)
{
    m_courseId = newCourseId;
}

void EducationWork::setWorkFormId(int newWorkFormId)
{
    m_workFormId = newWorkFormId;
}

void EducationWork::setGroupCount(int newGroupCount)
{
    m_groupCount = newGroupCount;
}

void EducationWork::setComments(const QString &newComments)
{
    m_comments = newComments;
}

void EducationWork::setOrderPalce(int newOrderPalce)
{
    m_orderPalce = newOrderPalce;
}
