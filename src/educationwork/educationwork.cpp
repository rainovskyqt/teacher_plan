#include "educationwork.h"
#include "modeleducationwork.h"

#include <misc/months.h>

using HF = ModelEducationWork::HourFields;

Hour::Hour(QObject *parent)
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

EducationWork::EducationWork(QObject *parent)
    : QObject{parent}
{
    m_id = 0;
    m_disciplineId = 0;
    m_courseId = 0;
    m_workFormId = 0;
    m_groupCount = 0;
    m_comments = "";
    m_orderPalce = 0;
    for(int i = 1; i < Months::get()->weekCount() + 1; ++i){
        m_hours.insert(i, new Hour());
    }
}

int EducationWork::id() const
{
    return m_id;
}

void EducationWork::setId(int newId)
{
    m_id = newId;
}

int EducationWork::disciplineId() const
{
    return m_disciplineId;
}

void EducationWork::setDisciplineId(int newDisciplineId)
{
    m_disciplineId = newDisciplineId;
}

int EducationWork::courseId() const
{
    return m_courseId;
}

void EducationWork::setCourseId(int newCourseId)
{
    m_courseId = newCourseId;
}

int EducationWork::workFormId() const
{
    return m_workFormId;
}

void EducationWork::setWorkFormId(int newWorkFormId)
{
    m_workFormId = newWorkFormId;
}

int EducationWork::groupCount() const
{
    return m_groupCount;
}

void EducationWork::setGroupCount(int newGroupCount)
{
    m_groupCount = newGroupCount;
}

QString EducationWork::comments() const
{
    return m_comments;
}

void EducationWork::setComments(const QString &newComments)
{
    m_comments = newComments;
}

int EducationWork::orderPalce() const
{
    return m_orderPalce;
}

void EducationWork::setOrderPalce(int newOrderPalce)
{
    m_orderPalce = newOrderPalce;
}

void EducationWork::setHours(QString hoursStr)
{
    QStringList splittedHours = hoursStr.split(";", Qt::SkipEmptyParts);
    for(const QString &hourRow : qAsConst(splittedHours)){
        QStringList h = hourRow.split(",");
        int week = h.at((int)HF::HourWeek).toInt();

        Hour *current = m_hours.value(week);
        current->setId(h.at((int)HF::HourId).toInt());
        current->setWeek(week);
        current->setPlan(h.at((int)HF::HourPlanValue).toInt());
        current->setFact(h.at((int)HF::HourFactValue).toInt());
        m_hours.insert(week, current);
    }
}

QHash<int, Hour *> EducationWork::hours() const
{
    return m_hours;
}
