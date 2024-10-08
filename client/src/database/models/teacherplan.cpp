#include "teacherplan.h"

#include <QJsonDocument>

TeacherPlan::TeacherPlan(QObject *parent):
    QObject(parent)
{
    m_approveUserId = 0;
//    m_hours = QMap<int, PlanTime*>();
    m_changed = false;
    m_baseId = 0;
    m_rate = 1;
    m_statusId = Development;
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

int TeacherPlan::approveUserId() const
{
    return m_approveUserId;
}

void TeacherPlan::setApproveUserId(int approveUserId)
{
    m_approveUserId = approveUserId;
}

QDate TeacherPlan::approveDate() const
{
    return m_approveDate;
}

void TeacherPlan::setApproveDate(const QDate &newApproveDate)
{
    m_approveDate = newApproveDate;
}

void TeacherPlan::addEducationaWork(EducationalWork *work)
{
    m_educationWork.append(work);
}

void TeacherPlan::removeEducationaWork(EducationalWork *work)
{
    m_educationWork.removeOne(work);
}

QVector<EducationalWork *> TeacherPlan::educationWork()
{
    return m_educationWork;
}

UserPost TeacherPlan::getStaff() const
{
    return staff;
}

void TeacherPlan::setStaff(const UserPost &newStaff)
{
    staff = newStaff;
}

//QMap<int, PlanTime*> TeacherPlan::hours() const
//{
//    return m_hours;
//}

//void TeacherPlan::setHours(const QMap<int, PlanTime *> &newHours)
//{
//    auto times = m_hours.values();
//    qDeleteAll(times);
//    m_hours.clear();
//    m_hours = newHours;
//}

//void TeacherPlan::addHour(int orderPlace, PlanTime *time)
//{
//    m_hours.insert(orderPlace, time);
//}
