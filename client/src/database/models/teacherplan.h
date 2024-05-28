#ifndef TEACHERPLAN_H
#define TEACHERPLAN_H

#include <QObject>
#include <QDate>
#include <QString>
#include "login/user.h"
#include "plantime.h"

class TeacherPlan : public QObject
{

    Q_OBJECT

public:

    enum Status{
        Development = 1,
        OnApproved,
        Approveded
    };

    explicit TeacherPlan(QObject *parent = nullptr);

    bool isChanged() const;
    void setChanged(bool newChanget);

    int baseId() const;
    void setBaseId(int newBaseId);

    int userId() const;
    void setUserId(int newUserId);

    int departmentId() const;
    void setDepartmentId(int newDepartmentId);

    int postId() const;
    void setPostId(int newPostId);

    int yearId() const;
    void setYearId(int newYearId);

    int statusId() const;
    void setStatusId(int newStatusId);

    double rate() const;
    void setRate(double newRate);

    QString protocolNumber() const;
    void setProtocolNumber(const QString &newProtocolNumber);

    QDate protocolDate() const;
    void setProtocolDate(const QDate &newProtocolDate);

    User *approveUser() const;
    void setApproveUser(User *newApproveUser);

    QDate approveDate() const;
    void setApproveDate(const QDate &newApproveDate);

    QMap<int, PlanTime*> hours() const;
    void setHours(const QMap<int, PlanTime*> &newHours);

private:
    bool m_changed;
    int m_baseId;
    int m_userId;
    int m_departmentId;
    int m_postId;
    int m_yearId;
    int m_statusId;
    double m_rate;
    QString m_protocolNumber;
    QDate m_protocolDate;
    User* m_approveUser;
    QDate m_approveDate;
    QMap<int, PlanTime*> m_hours;

    // User m_departmentBoss;
};

#endif // TEACHERPLAN_H
