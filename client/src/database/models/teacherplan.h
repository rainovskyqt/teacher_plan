#ifndef TEACHERPLAN_H
#define TEACHERPLAN_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QVector>
#include "login/user.h"
#include "plantime.h"
#include "database/models/datamodels.h"

class EducationalWork;

class PlansList : public QObject
{
public:
    explicit PlansList(int id, int user, int year, int department, int post, QObject *parent = nullptr) : QObject(parent) {
        m_id = id;
        m_user = user;
        m_year = year;
        m_department = department;
        m_post = post;
    }

    int id() const {return m_id;}
    int user() const {return m_user;}
    int year() const {return m_year;}
    int department() const {return m_department;}
    int post() const {return m_post;}

private:
    int m_id;
    int m_user;
    int m_year;
    int m_department;
    int m_post;
};

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
    void setChanged(bool newChanged);

    int baseId() const;
    void setBaseId(int newBaseId);

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

    int approveUserId() const;
    void setApproveUserId(int approveUserId);

    QDate approveDate() const;
    void setApproveDate(const QDate &newApproveDate);

    void addEducationaWork(EducationalWork* work);
    void removeEducationaWork(EducationalWork* work);
    QVector<EducationalWork*> educationWork();

    UserPost getStaff() const;
    void setStaff(const UserPost &newStaff);

    QString comments() const;
    void setComments(const QString &newComments);

private:
    bool m_changed;
    int m_baseId;
    UserPost staff;
    int m_yearId;
    int m_statusId;
    double m_rate;
    QString m_protocolNumber;
    QDate m_protocolDate;
    int m_approveUserId;
    QDate m_approveDate;
    QVector<EducationalWork*> m_educationWork;
    QString m_comments;

    // User m_departmentBoss;
};

#endif // TEACHERPLAN_H
