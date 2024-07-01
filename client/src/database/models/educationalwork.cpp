#include "educationalwork.h"

EducationalWork::EducationalWork(int planId, QObject *parent) : TeacherWork(planId, parent)
{
    m_disciplineId = 1;
    m_workFormId = 1;
    m_groupId = 1;
    m_comments = QString();
    m_workType = Educational;
}

int EducationalWork::disciplineId() const
{
    return m_disciplineId;
}

void EducationalWork::setDisciplineId(int newDisciplineId)
{
    m_disciplineId = newDisciplineId;
}

int EducationalWork::workFormId() const
{
    return m_workFormId;
}

void EducationalWork::setWorkFormId(int newWorkFormId)
{
    m_workFormId = newWorkFormId;
}

int EducationalWork::groupId() const
{
    return m_groupId;
}

void EducationalWork::setGroupId(int newGroupId)
{
    m_groupId = newGroupId;
}

const QString &EducationalWork::comments() const
{
    return m_comments;
}

void EducationalWork::setComments(const QString &newComments)
{
    m_comments = newComments;
}

