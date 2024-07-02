#ifndef TEACHERWORK_H
#define TEACHERWORK_H

#include <QObject>
#include "datamodels.h"

class TeacherWork : public QObject
{
    Q_OBJECT
public:
    explicit TeacherWork(int planId, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);

    WorkType workType() const;

    int planId() const;

signals:

protected:
    int m_baseId;
    int m_planId;
    WorkType m_workType;
};

#endif // TEACHERWORK_H
