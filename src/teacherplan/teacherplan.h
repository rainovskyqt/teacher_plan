#ifndef TEACHERPLAN_H
#define TEACHERPLAN_H

#include <QDate>
#include <QObject>

#include "database/types.h"

class TeacherPlan : public QObject
{
    Q_OBJECT
public:
    explicit TeacherPlan(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    int staffId() const;
    void setStaffId(int newStaffId);
    double rate() const;
    void setRate(double newRate);
    PlanStatus status() const;
    void setStatus(PlanStatus newStatus);
    int approvedUserId() const;
    void setApprovedUserId(int newApprovedUserId);
    QDate approvedDate() const;
    void setApprovedDate(const QDate &newApprovedDate);
    int departmentBossSignId() const;
    void setDepartmentBossSignId(int newDepartmentBossSignId);
    QString protocolNumber() const;
    void setProtocolNumber(const QString &newProtocolNumber);
    QDate protocolDate() const;
    void setProtocolDate(const QDate &newProtocolDate);
    QString comments() const;
    void setComments(const QString &newComments);

signals:

private:
    int m_id;
    int m_staffId;
    double m_rate;
    PlanStatus m_status;
    int m_approvedUserId;
    QDate m_approvedDate;
    int m_departmentBossSignId;
    QString m_protocolNumber;
    QDate m_protocolDate;
    QString m_comments;
};

#endif // TEACHERPLAN_H
