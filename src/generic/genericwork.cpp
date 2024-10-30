#include "genericwork.h"

GenericWork::GenericWork(WorkType work, int planId, QObject *parent)
    : QObject(parent)
{
    m_id = 0;
    m_planId = planId;
    m_workType = work;
    m_workFormId = 0;
    m_semester = 0;
    m_complite = QString();
    m_planHours = 0;
    m_factHours = 0;
    m_orderPlace = 0;
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

WorkType GenericWork::workType() const
{
    return m_workType;
}

void GenericWork::setWorkType(WorkType newWorkType)
{
    m_workType = newWorkType;
}

int GenericWork::orderPlace() const
{
    return m_orderPlace;
}

void GenericWork::setOrderPlace(int newOrderPlace)
{
    m_orderPlace = newOrderPlace;
}

int GenericWork::id() const
{
    return m_id;
}

void GenericWork::setId(int newId)
{
    m_id = newId;
}

void GenericWork::setWorkFormId(int newWorkFormId)
{
    m_workFormId = newWorkFormId;
}
