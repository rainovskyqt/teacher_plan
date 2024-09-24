#ifndef TEACHERWORK_H
#define TEACHERWORK_H

#include <QObject>
#include "datamodels.h"

class TeacherWork : public QObject
{
    Q_OBJECT
public:

    enum Status{
        Development,
        Aproved,
        Closed
    };

    explicit TeacherWork(int planId, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);

    WorkType workType() const;

    int planId() const;

    void setOrderPlace(int newOrderPlace);

    int orderPlace() const;

signals:

protected:
    int m_baseId;
    int m_planId;
    int m_orderPlace;
    WorkType m_workType;
};

#endif // TEACHERWORK_H
