#include "comment.h"

Comment::Comment()
{}

Comment::Comment(const Comment &other) :
    m_id(other.id())
    ,m_date(other.date())
    ,m_version(other.version())
    ,m_comment(other.comment())
{}

void Comment::operator=(const Comment &other)
{
    m_id = other.id();
    m_date = other.date();
    m_version = other.version();
    m_comment = other.comment();
}

int Comment::id() const
{
    return m_id;
}

void Comment::setId(int newId)
{
    m_id = newId;
}

QDate Comment::date() const
{
    return m_date;
}

QString Comment::dateString() const
{
    return m_date.toString("dd.MM.yyyy");
}

void Comment::setDate(const QDate &newDate)
{
    m_date = newDate;
}

QString Comment::version() const
{
    return m_version;
}

void Comment::setVersion(const QString &newVersion)
{
    m_version = newVersion;
}

QString Comment::comment() const
{
    return m_comment;
}

void Comment::setComment(const QString &newComment)
{
    m_comment = newComment;
}
