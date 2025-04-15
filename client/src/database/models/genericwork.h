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

signals:

private:
    int m_workFormId;
    int m_semester;
    QString m_complite;
    int m_planHours;
    int m_factHours;
};

#endif // GENERICWORK_H
