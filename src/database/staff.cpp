#include "staff.h"

Staff::Staff(int id, int userId, int departmentId, int postId, double rate, int year, QObject *parent) :
    Staff(id, userId, departmentId, "", postId, "", false, rate, year)
{}

Staff::Staff(int id, int userId, int departmentId, QString departmentName,
             int postId, QString postName, bool main, double rate, int year, QObject *parent)
    : QObject{parent}
    , m_id{id}
    , m_userId{userId}
    , m_departmentId{departmentId}
    , m_departmentName{departmentName}
    , m_postId{postId}
    , m_postName{postName}
    , m_main{main}
    , m_rate{rate}
    , m_year{year}
{}

const int Staff::id() const
{
    return m_id;
}

const int Staff::departmentId() const
{
    return m_departmentId;
}

const QString &Staff::departmentName() const
{
    return m_departmentName;
}

const int Staff::postId() const
{
    return m_postId;
}

const QString &Staff::postName() const
{
    return m_postName;
}

bool Staff::isMain() const
{
    return m_main;
}

double Staff::rate() const
{
    return m_rate;
}

int Staff::year() const
{
    return m_year;
}

int Staff::userId() const
{
    return m_userId;
}
