#include "totaltimelist.h"

TotalTimeList::TotalTimeList(QObject *parent)
    : QObject{parent}
    , m_maxHoursCount{1512}
{}

int TotalTimeList::maxHoursCount(double rate) const
{
    return m_maxHoursCount * rate;
}

void TotalTimeList::setTime()
{

}
