#include "month.h"

Month::Month(QObject *parent) : QObject(parent)
{
    m_months = {
        {January, "Январь"},
        {February, "Февраль"},
        {March, "Март"},
        {April, "Апрель"},
        {May, "Май"},
        {June, "Июнь"},
        {July, "Июль"},
        {August, "Август"},
        {September, "Сентябрь"},
        {October," Октябрь"},
        {November," Ноябрь"},
        {December," Декабрь"},
        {Other, "Перебор"}
    };
}

QString Month::name(Months month)
{
    return m_months.value(month);
}
