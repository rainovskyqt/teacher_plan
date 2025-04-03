#include "printdata.h"

PrintData::PrintData(QObject *parent)
    : QObject{parent}
    , m_secondSemester(false)
{}

bool PrintData::isSecond() const
{
    return m_secondSemester;
}

void PrintData::setSecondSemester(bool newSecondSemester)
{
    m_secondSemester = newSecondSemester;
}

