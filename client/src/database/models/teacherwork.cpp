#include "teacherwork.h"

TeacherWork::TeacherWork(int planId, QObject *parent)
    : QObject{parent}
{
    m_baseId = 0;
    m_planId = planId;
}

int TeacherWork::baseId() const
{
    return m_baseId;
}

void TeacherWork::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

WorkType TeacherWork::workType() const
{
    return m_workType;
}

int TeacherWork::planId() const
{
    return m_planId;
}
