#include "printgenericwork.h"

PrintGenericWork::PrintGenericWork(QObject *parent)
    : PrintData{parent}
    , m_approvedPost(QString())
{}

QString PrintGenericWork::approvedPost() const
{
    return m_approvedPost;
}

void PrintGenericWork::setApprovedPost(const QString &newApprovedPost)
{
    m_approvedPost = newApprovedPost;
}

QString PrintGenericWork::approvedUser() const
{
    return m_approvedUser;
}

void PrintGenericWork::setApprovedUser(const QString &newApprovedUser)
{
    m_approvedUser = newApprovedUser;
}
