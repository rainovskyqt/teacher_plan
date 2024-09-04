#ifndef GENERICWORK_H
#define GENERICWORK_H

#include <QObject>
#include "database/models/datamodels.h"
#include "teacherwork.h"

class GenericWork : public TeacherWork
{
    Q_OBJECT
public:
    explicit GenericWork(WorkType work, int planId, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    WorkType type() const;

signals:

private:
    WorkType m_type;
};

#endif // GENERICWORK_H
