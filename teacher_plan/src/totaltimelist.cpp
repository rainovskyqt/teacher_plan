#include "totaltimelist.h"

TotalTimeList::TotalTimeList(QObject *parent)
    : QObject{parent}
    , m_maxHoursCount{1512}
{}

int TotalTimeList::maxHoursCount() const
{
    return m_maxHoursCount;
}

void TotalTimeList::setTime()
{

}
