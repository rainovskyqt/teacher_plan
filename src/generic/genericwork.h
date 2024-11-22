#ifndef GENERICWORK_H
#define GENERICWORK_H

#include <QObject>
#include "database/types.h"

class GenericWork : public QObject
{
    Q_OBJECT
public:
    explicit GenericWork(WorkType work, int planId, QObject *parent = nullptr);

    int workFormId() const;
    void setWorkFormId(int newWorkFormId);

    int semester() const;
    void setSemester(int newSemester);

    QString complite() const;
    void setComplite(const QString &newComplite);

    int planHours() const;
    void setPlanHours(int newPlanHours);

    int factHours() const;
    void setFactHours(int newFactHours);


    WorkType workType() const;
    void setWorkType(WorkType newWorkType);

    int orderPlace() const;
    void setOrderPlace(int newOrderPlace);

    int id() const;
    void setId(int newId);

signals:

private:
    int m_id;
    int m_planId;
    int m_workFormId;
    int m_semester;
    QString m_complite;
    int m_planHours;
    int m_factHours;
    WorkType m_workType;
    int m_orderPlace;
};

#endif // GENERICWORK_H
