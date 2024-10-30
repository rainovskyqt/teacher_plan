#include "teacherplan.h"

TeacherPlan::TeacherPlan(QObject *parent)
    : QObject{parent}
{
    m_id = 0;
    m_staffId = 0;
    m_rate = 1;
    m_status = PlanStatus::NotSet;
    m_approvedUserId = 0;
    m_approvedDate;
    m_departmentBossSignId = 0;
    m_protocolNumber = QString();
    m_protocolDate;
    m_comments = QString();
}

int TeacherPlan::id() const
{
    return m_id;
}

void TeacherPlan::setId(int newId)
{
    m_id = newId;
}

int TeacherPlan::staffId() const
{
    return m_staffId;
}

void TeacherPlan::setStaffId(int newStaffId)
{
    m_staffId = newStaffId;
}

double TeacherPlan::rate() const
{
    return m_rate;
}

void TeacherPlan::setRate(double newRate)
{
    m_rate = newRate;
}

PlanStatus TeacherPlan::status() const
{
    return m_status;
}

void TeacherPlan::setStatus(PlanStatus newStatus)
{
    m_status = newStatus;
}

int TeacherPlan::approvedUserId() const
{
    return m_approvedUserId;
}

void TeacherPlan::setApprovedUserId(int newApprovedUserId)
{
    m_approvedUserId = newApprovedUserId;
}

QDate TeacherPlan::approvedDate() const
{
    return m_approvedDate;
}

void TeacherPlan::setApprovedDate(const QDate &newApprovedDate)
{
    m_approvedDate = newApprovedDate;
}

int TeacherPlan::departmentBossSignId() const
{
    return m_departmentBossSignId;
}

void TeacherPlan::setDepartmentBossSignId(int newDepartmentBossSignId)
{
    m_departmentBossSignId = newDepartmentBossSignId;
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

QString TeacherPlan::comments() const
{
    return m_comments;
}

void TeacherPlan::setComments(const QString &newComments)
{
    m_comments = newComments;
}
