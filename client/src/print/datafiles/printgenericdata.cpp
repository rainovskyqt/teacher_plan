#include "printgenericdata.h"

PrintGenericWork::PrintGenericWork(int number, const QString &name, int plane, int fact, const QString &comments, QObject *parent) :
    QObject(parent)
    , m_number(number)
    , m_name(name)
    , m_plane(plane)
    , m_fact(fact)
    , m_comments(comments)
{}

int PrintGenericWork::number() const
{
    return m_number;
}

const QString PrintGenericWork::name() const
{
    return m_name;
}

int PrintGenericWork::plane() const
{
    return m_plane;
}

int PrintGenericWork::fact() const
{
    return m_fact;
}

const QString PrintGenericWork::getComments() const
{
    return m_comments;
}

PrintGenericData::PrintGenericData(QObject *parent)
    : PrintData{parent}
    , m_approvedPost(QString())
{}

QString PrintGenericData::approvedPost() const
{
    return m_approvedPost;
}

void PrintGenericData::setApprovedPost(const QString &newApprovedPost)
{
    m_approvedPost = newApprovedPost;
}

QString PrintGenericData::approvedUser() const
{
    return m_approvedUser;
}

void PrintGenericData::setApprovedUser(const QString &newApprovedUser)
{
    m_approvedUser = newApprovedUser;
}

const QHash<int, PrintGenericWork *> PrintGenericData::works() const
{
    return m_works;
}

void PrintGenericData::addWork(int position, PrintGenericWork *work)
{
    if(auto w = m_works.value(position))
        w->deleteLater();

    m_works.insert(position, work);
}

QString PrintGenericData::department() const
{
    return m_department;
}

void PrintGenericData::setDepartment(const QString &newDepartment)
{
    m_department = newDepartment;
}

QString PrintGenericData::workName() const
{
    return m_workName;
}

void PrintGenericData::setWorkName(const QString &newWorkName)
{
    m_workName = newWorkName;
}
