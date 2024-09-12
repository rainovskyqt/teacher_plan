#ifndef EDUCATIONALWORK_H
#define EDUCATIONALWORK_H

#include "teacherwork.h"

#include <QObject>

class EducationalWork : public TeacherWork
{
public:
    explicit EducationalWork(int planId, QObject *parent = nullptr);

    int disciplineId() const;
    void setDisciplineId(int newDisciplineId);
    int workFormId() const;
    void setWorkFormId(int newWorkFormId);
    int courseId() const;
    void setCourseId(int newCourseId);
    int groupCount() const;
    void setGroupCount(int newGroupCount);
    const QString &comments() const;
    void setComments(const QString &newComments);


signals:

private:
    int m_disciplineId;
    int m_workFormId;
    int m_courseId;
    int m_groupCount;
    QString m_comments;
};

#endif // EDUCATIONALWORK_H
