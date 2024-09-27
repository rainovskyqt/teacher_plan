#include "staff.h"

Staff::Staff(int id, int departmentId, QString departmentName, int postId, QString postName, bool main, QObject *parent)
    : QObject{parent}
    , m_id{id}
    , m_departmentId{departmentId}
    , m_departmentName{departmentName}
    , m_postId{postId}
    , m_postName{postName}
    , m_main{main}
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
