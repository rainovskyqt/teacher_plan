#include "printcomplite.h"

PrintComplite::PrintComplite(QObject *parent)
    : PrintData{parent}
{}

QString PrintComplite::comments() const
{
    return m_comments;
}

void PrintComplite::setComments(const QString &newComments)
{
    m_comments = newComments;
}

void PrintComplite::setValue(int month, int work, QString value)
{
    m_values.insert(month, qMakePair(work, value));
}

QMultiMap<int, QPair<int, QString> > PrintComplite::values() const
{
    return m_values;
}

int PrintComplite::totalHours() const
{
    return m_totalHours;
}

void PrintComplite::setTotalHours(int newTotalHours)
{
    m_totalHours = newTotalHours;
}
