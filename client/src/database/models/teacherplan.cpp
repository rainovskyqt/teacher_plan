#include "teacherplan.h"

TeacherPlan::TeacherPlan(QObject *parent):
    QObject(parent),
    m_approveUser{nullptr}
{
    m_hours = QMap<int, PlanTime*>();
    m_changed = false;
}

bool TeacherPlan::isChanged() const
{
    return m_changed;
}

void TeacherPlan::setChanged(bool newChanged)
{
    m_changed = newChanged;
}

int TeacherPlan::baseId() const
{
    return m_baseId;
}

void TeacherPlan::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

int TeacherPlan::userId() const
{
    return m_userId;
}

void TeacherPlan::setUserId(int newUserId)
{
    m_userId = newUserId;
}

int TeacherPlan::departmentId() const
{
    return m_departmentId;
}

void TeacherPlan::setDepartmentId(int newDepartmentId)
{
    m_departmentId = newDepartmentId;
}

int TeacherPlan::postId() const
{
    return m_postId;
}

void TeacherPlan::setPostId(int newPostId)
{
    m_postId = newPostId;
}

int TeacherPlan::yearId() const
{
    return m_yearId;
}

void TeacherPlan::setYearId(int newYearId)
{
    m_yearId = newYearId;
}

int TeacherPlan::statusId() const
{
    return m_statusId;
}

void TeacherPlan::setStatusId(int newStatusId)
{
    m_statusId = newStatusId;
}

double TeacherPlan::rate() const
{
    return m_rate;
}

void TeacherPlan::setRate(double newRate)
{
    m_rate = newRate;
}

QString TeacherPlan::protocolNumber() const
{
    return m_protocolNumber;
}

void TeacherPlan::setProtocolNumber(const QString &newProtocolNumber)
{
    m_protocolNumber = newProtocolNumber;
}

QDate TeacherPlan::protocolDate() const
{
    return m_protocolDate;
}

void TeacherPlan::setProtocolDate(const QDate &newProtocolDate)
{
    m_protocolDate = newProtocolDate;
}

User *TeacherPlan::approveUser() const
{
    return m_approveUser;
}

void TeacherPlan::setApproveUser(User *newApproveUser)
{
    m_approveUser = newApproveUser;
}

QDate TeacherPlan::approveDate() const
{
    return m_approveDate;
}

void TeacherPlan::setApproveDate(const QDate &newApproveDate)
{
    m_approveDate = newApproveDate;
}

QMap<int, PlanTime*> TeacherPlan::hours() const
{
    return m_hours;
}

void TeacherPlan::setHours(const QMap<int, PlanTime *> &newHours)
{
    m_hours = newHours;
}
