#include "educationalwork.h"

EducationalWork::EducationalWork(QObject *parent) : QObject(parent)
{
    m_disciplineId = 0;
    m_workFormId = 0;
    m_groupId = 0;
    m_comments = QString();
}

int EducationalWork::baseId() const
{
    return m_baseId;
}

void EducationalWork::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
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

