#include "genericwork.h"

GenericWork::GenericWork(WorkType work, int planId, QObject *parent)
    : TeacherWork(planId, parent)
{
    m_workType = work;
    m_workFormId = 0;
    m_semester = 0;
    m_complite = QString();
    m_orderplace = 0;
    m_planHours = 0;
    m_factHours = 0;
}

int GenericWork::workFormId() const
{
    return m_workFormId;
}

int GenericWork::semester() const
{
    return m_semester;
}

void GenericWork::setSemester(int newSemester)
{
    m_semester = newSemester;
}

QString GenericWork::complite() const
{
    return m_complite;
}

void GenericWork::setComplite(const QString &newComplite)
{
    m_complite = newComplite;
}

int GenericWork::orderplace() const
{
    return m_orderplace;
}

void GenericWork::setOrderplace(int newOrderplace)
{
    m_orderplace = newOrderplace;
}

int GenericWork::planHours() const
{
    return m_planHours;
}

void GenericWork::setPlanHours(int newPlanHours)
{
    m_planHours = newPlanHours;
}

int GenericWork::factHours() const
{
    return m_factHours;
}

void GenericWork::setFactHours(int newFactHours)
{
    m_factHours = newFactHours;
}

void GenericWork::setWorkFormId(int newWorkFormId)
{
    m_workFormId = newWorkFormId;
}
