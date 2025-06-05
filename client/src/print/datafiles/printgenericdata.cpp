#include "printgenericdata.h"

#include <QVector>

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
    , m_totalPlane(0)
    , m_totalFact(0)
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

int PrintGenericData::totalPlane() const
{
    return m_totalPlane;
}

void PrintGenericData::setTotalPlane(int newTotalPlane)
{
    m_totalPlane = newTotalPlane;
}

int PrintGenericData::totalFact() const
{
    return m_totalFact;
}

void PrintGenericData::setTotalFact(int newTotalFact)
{
    m_totalFact = newTotalFact;
}

QVector<QMap<int, PrintGenericWork *> > PrintGenericData::works()
{
    auto w = splitData(m_works, true);
    return w;
}
