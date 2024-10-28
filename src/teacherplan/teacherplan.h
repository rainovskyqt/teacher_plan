#ifndef TEACHERPLAN_H
#define TEACHERPLAN_H

#include <QDate>
#include <QObject>

class TeacherPlan : public QObject
{
    Q_OBJECT
public:
    explicit TeacherPlan(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    int staffId() const;
    void setStaffId(int newStaffId);
    int yearId() const;
    void setYearId(int newYearId);
    double rate() const;
    void setRate(double newRate);
    int statusId() const;
    void setStatusId(int newStatusId);
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
    int m_yearId;
    double m_rate;
    int m_statusId;
    int m_approvedUserId;
    QDate m_approvedDate;
    int m_departmentBossSignId;
    QString m_protocolNumber;
    QDate m_protocolDate;
    QString m_comments;
};

#endif // TEACHERPLAN_H
