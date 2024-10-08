#include "educationalwork.h"

EducationalWork::EducationalWork(int planId, QObject *parent) : TeacherWork(planId, parent)
{
    m_disciplineId = 0;
    m_workFormId = 0;
    m_courseId = 0;
    m_groupCount = 1;
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

int EducationalWork::courseId() const
{
    return m_courseId;
}

void EducationalWork::setCourseId(int newCourseId)
{
    m_courseId = newCourseId;
}

int EducationalWork::groupCount() const
{
    return m_groupCount;
}

void EducationalWork::setGroupCount(int newGroupCount)
{
    m_groupCount = newGroupCount;
}

const QString &EducationalWork::comments() const
{
    return m_comments;
}

void EducationalWork::setComments(const QString &newComments)
{
    m_comments = newComments;
}

