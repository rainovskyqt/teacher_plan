#include "months.h"

#include <database/database.h>

#include <QVariant>
#include <QDebug>
#include <QDate>

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

QMap<int, QPair<int, int> > Months::weekDates() const
{
    return m_weeksDates;
}

void Months::loadSettings(int year)
{
    m_monthWeeks.clear();

    QString queryString = R"(SELECT WS.id, WS.year_id, WS.total_count, WS.start_week_dates,
                            WS.january, WS.february, WS.march, WS.april, WS.may, WS.june, WS.july, WS.august, WS.september,
                            WS.october, WS.november, WS.december,
                            EY.begin_year
                            FROM weeks_settings WS
                            INNER JOIN educational_years EY ON EY.id = WS.year_id
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
    setWeeksDates(answer.value("start_week_dates").toString(),
                  answer.value("begin_year").toInt(),
                  answer.value("total_count").toInt());
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

void Months::setWeeksDates(QString firstWeek, int year, int count)
{
    m_weeksDates.clear();
    QStringList dates = firstWeek.split(";");
    QDate start = QDate(year, 9, dates.at(1).toInt());
    m_weeksDates.insert(1, qMakePair(dates.at(0).toInt(), dates.at(1).toInt()));
    for(int i = 2; i < count + 1; ++i){
        int sd, ed;
        start = start.addDays(1);
        sd = start.toString("dd").toInt();
        start = start.addDays(6);
        ed = start.toString("dd").toInt();
        m_weeksDates.insert(i, qMakePair(sd, ed));
    }
}
