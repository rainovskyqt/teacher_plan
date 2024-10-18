#include "months.h"

#include <database/database.h>

#include <QVariant>
#include <QDebug>

Q_GLOBAL_STATIC(Months, globalInst)

Months::Months(QObject *parent) : QObject(parent)
{
}

Months *Months::get()
{
    return globalInst();
}

int Months::weekCount() const
{
    return m_weeksDates.count();
}

QString Months::name(Month month) const
{
    switch (month) {
    case January:
        return "Январь";
    case February:
        return "Февраль";
    case March:
        return "Март";
    case April:
        return "Апрель";
    case May:
        return "Май";
    case June:
        return "Июнь";
    case July:
        return "Июль";
    case August:
        return "Август";
    case September:
        return "Сентябрь";
    case October:
        return "Октябрь";
    case November:
        return "Ноябрь";
    case December:
        return "Декабрь";
    default:
        return "Перебор";
    }
}

QList<Months::Month> Months::educationYearList() const
{
    QList<Months::Month> list;
    int m = (int)September;
    for(int i = 0; i < 12; ++i){
        if(m == (int)July || m == (int)August)
            continue;
        else if(m == (int)Other)
            m = (int)January;
        list.append((Month)m);
        ++m;;
    }
    return list;
}

bool Months::isFirstSemester(Month month) const
{
    if(month >= Month::February && month <= Month::June)
        return true;
    else
        return false;
}

bool Months::isFirstSemester(int week) const
{
    return week < m_secondSemesterFirstWeek;
}

QPair<int, int> Months::monthWeeks(Month month) const
{
    return m_monthWeeks.value(month);
}

QPair<int, int> Months::weekDates(int week) const
{
    return m_weeksDates.value(week);
}

void Months::loadSettings(int year)
{
    m_monthWeeks.clear();

    QString queryString = R"(SELECT id, year_id, total_count, start_week_dates,
                             january, february, march, april, may, june, july, august, september, october, november, december
                             FROM weeks_settings
                             WHERE year_id = :year)";
    Arguments args;
    args.insert(":year", QVariant(year));

    auto answer = Database::get()->selectQuery(queryString, args);
    if (!answer.next())
        return;

    auto months = educationYearList();
    int start = 1;
    int monthSmooth = 3;
    for(auto m : months){
        int count = answer.value((int)m + monthSmooth).toInt();
        m_monthWeeks.insert(m, qMakePair(start, count));
        start += count;
    }

    countSecondSemesterFirstWeek();
}

void Months::countSecondSemesterFirstWeek()
{
    if(m_monthWeeks.isEmpty()){
        qDebug() << "Список недель по месецам пустой";
        return;
    }
    m_secondSemesterFirstWeek = 0;
    auto months = educationYearList();
    for(auto m : months){
        if(m == February)
            break;
        m_secondSemesterFirstWeek += m_monthWeeks.value(m).second;          // В second хранится количество недель
    }
    ++m_secondSemesterFirstWeek;                //Повышаем на еденицу, что бы получить первую неделю второго семестра
}
