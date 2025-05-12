#include "printstudydata.h"
#include <QVector>

PrintStudyWork::PrintStudyWork(int position, QString name, int totalPlaneI, int totalFactI,
                               int totalPlaneII, int totalFactII, int totalPlaneYear, int totalFactYear, QString comments, QObject *parent) :
    QObject(parent)
{
    m_position = position;
    m_name = name;
    m_totalPlaneI = totalPlaneI;
    m_totalFactI = totalFactI;
    m_totalPlaneII = totalPlaneII;
    m_totalFactII = totalFactII;
    m_totalPlaneYear = totalPlaneYear;
    m_totalFactYear = totalFactYear;
    m_comments = comments;
}

int PrintStudyWork::position() const
{
    return m_position;
}

QString PrintStudyWork::name() const
{
    return m_name;
}

int PrintStudyWork::totalPlaneI() const
{
    return m_totalPlaneI;
}

int PrintStudyWork::totalFactI() const
{
    return m_totalFactI;
}

int PrintStudyWork::totalPlaneII() const
{
    return m_totalPlaneII;
}

int PrintStudyWork::totalFactII() const
{
    return m_totalFactII;
}

int PrintStudyWork::totalPlaneYear() const
{
    return m_totalPlaneYear;
}

int PrintStudyWork::totalFactYear() const
{
    return m_totalFactYear;
}

QMap<int, QPair<int, int>> PrintStudyWork::hours() const
{

    return m_hours;
}

void PrintStudyWork::addHours(int week, int plane, int fact)
{
    m_hours.insert(week, qMakePair(plane, fact));
}

QString PrintStudyWork::comments() const
{
    return m_comments;
}

void PrintStudyWork::setComments(const QString &newComments)
{
    m_comments = newComments;
}

//======================================== PrintStudyData ==============================================
PrintStudyData::PrintStudyData(QObject *parent) : PrintData(parent)
{

}

int PrintStudyData::totalYearPlane() const
{
    return m_totalYearPlane;
}

void PrintStudyData::setTotalYearPlane(int newTotalYearPlane)
{
    m_totalYearPlane = newTotalYearPlane;
}

int PrintStudyData::totalYearFact() const
{
    return m_totalYearFact;
}

void PrintStudyData::setTotalYearFact(int newTotalYearFact)
{
    m_totalYearFact = newTotalYearFact;
}

QMap<int, QPair<int, int> > PrintStudyData::weekTotal() const
{
    return m_weekTotal;
}

void PrintStudyData::addWeekTotal(int week, int plane, int fact)
{
    m_weekTotal.insert(week, qMakePair(plane, fact));
}

void PrintStudyData::addWork(int position, PrintStudyWork *work)
{
    auto cWork = m_works.value(position);
    if(cWork)
        cWork->deleteLater();

    m_works.insert(position, work);
}

int PrintStudyData::totalFirstPlane() const
{
    return m_totalFirstPlane;
}

void PrintStudyData::setTotalFirstPlane(int newTotalFirstPlane)
{
    m_totalFirstPlane = newTotalFirstPlane;
}

int PrintStudyData::totalFirstFact() const
{
    return m_totalFirstFact;
}

void PrintStudyData::setTotalFirstFact(int newTotalFirstFact)
{
    m_totalFirstFact = newTotalFirstFact;
}

int PrintStudyData::totalSecondPlane() const
{
    return m_totalSecondPlane;
}

void PrintStudyData::setTotalSecondPlane(int newTotalSecondPlane)
{
    m_totalSecondPlane = newTotalSecondPlane;
}

int PrintStudyData::totalSecondFact() const
{
    return m_totalSecondFact;
}

void PrintStudyData::setTotalSecondFact(int newTotalSecondFact)
{
    m_totalSecondFact = newTotalSecondFact;
}

QVector<QMap<int, PrintStudyWork *> > PrintStudyData::works()
{
    auto w = splitData(m_works);
    return w;
}
