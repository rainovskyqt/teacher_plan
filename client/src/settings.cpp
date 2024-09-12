#include "settings.h"

Settings::Settings()
{
    loadWeeksCount();
    loadWeeks();
}

void Settings::loadWeeksCount()     //NOTE Побездать динамическое создние недель ТУТ
{
    m_weekCount = {
        {Month::Months::January, 4},
        {Month::Months::February, 4},
        {Month::Months::March, 4},
        {Month::Months::April, 5},
        {Month::Months::May, 4},
        {Month::Months::June, 5},
        {Month::Months::July, 5},
        {Month::Months::August, 4},
        {Month::Months::September, 4},
        {Month::Months::October, 5},
        {Month::Months::November, 4},
        {Month::Months::December, 5},
        {Month::Months::Other, 4}
    };

    m_weeks = {
        {1, Month::Months::September},
        {2, Month::Months::September},
        {3, Month::Months::September},
        {4, Month::Months::September},
        {5, Month::Months::October},
        {6, Month::Months::October},
        {7, Month::Months::October},
        {8, Month::Months::October},
        {9, Month::Months::October},
        {10, Month::Months::November},
        {11, Month::Months::November},
        {12, Month::Months::November},
        {13, Month::Months::November},
        {14, Month::Months::December},
        {15, Month::Months::December},
        {16, Month::Months::December},
        {17, Month::Months::December},
        {18, Month::Months::December},
        {19, Month::Months::January},
        {20, Month::Months::January},
        {21, Month::Months::January},
        {22, Month::Months::January},
        {23, Month::Months::February},
        {24, Month::Months::February},
        {25, Month::Months::February},
        {26, Month::Months::February},
        {27, Month::Months::March},
        {28, Month::Months::March},
        {29, Month::Months::March},
        {30, Month::Months::March},
        {31, Month::Months::April},
        {32, Month::Months::April},
        {33, Month::Months::April},
        {34, Month::Months::April},
        {35, Month::Months::April},
        {36, Month::Months::May},
        {37, Month::Months::May},
        {38, Month::Months::May},
        {39, Month::Months::May},
        {40, Month::Months::June},
        {41, Month::Months::June},
        {42, Month::Months::June},
        {43, Month::Months::June},
        {44, Month::Months::June}
    };
}

void Settings::loadWeeks()
{
    m_weeksDays = {
        {1, qMakePair(2, 8)},
        {2, qMakePair(9, 15)},
        {3, qMakePair(16, 22)},
        {4, qMakePair(23, 29)},
        {5, qMakePair(30, 6)},
        {6, qMakePair(7, 13)},
        {7, qMakePair(14, 20)},
        {8, qMakePair(21, 27)},
        {9, qMakePair(28, 3)},
        {10, qMakePair(4, 10)},
        {11, qMakePair(11, 17)},
        {12, qMakePair(18, 24)},
        {13, qMakePair(25, 1)},
        {14, qMakePair(2, 8)},
        {15, qMakePair(9, 15)},
        {16, qMakePair(16, 22)},
        {17, qMakePair(23, 29)},
        {18, qMakePair(30, 5)},
        {19, qMakePair(6, 12)},
        {20, qMakePair(13, 19)},
        {21, qMakePair(20, 26)},
        {22, qMakePair(27, 2)},
        {23, qMakePair(3, 9)},
        {24, qMakePair(10, 16)},
        {25, qMakePair(17, 23)},
        {26, qMakePair(24, 2)},
        {27, qMakePair(3, 9)},
        {28, qMakePair(10, 16)},
        {29, qMakePair(17, 23)},
        {30, qMakePair(24, 30)},
        {31, qMakePair(31, 6)},
        {32, qMakePair(7, 13)},
        {33, qMakePair(14, 20)},
        {34, qMakePair(21, 27)},
        {35, qMakePair(28, 4)},
        {36, qMakePair(5, 11)},
        {37, qMakePair(12, 18)},
        {38, qMakePair(19, 25)},
        {39, qMakePair(26, 1)},
        {40, qMakePair(2, 8)},
        {41, qMakePair(9, 15)},
        {42, qMakePair(16, 22)},
        {43, qMakePair(23, 29)},
        {44, qMakePair(30, 6)},
    };
}

Settings Settings::get()
{
    return Settings();
}

QString Settings::dbHost()
{
    return get<QString>("dbHost", "127.0.0.1");
    // return get<QString>("dbHost", "83.167.69.146");
}

void Settings::setDbHost(QString host)
{
    set("dbHost", host);
}

int Settings::dbPort()
{
    return get<int>("dbPort", 3306);
    // return get<int>("dbPort", 32138);
}

void Settings::setDbPort(int port)
{
    set("dbPort", port);
}

QString Settings::lastName()
{
    return get<QString>("lastName", "");
}

void Settings::setLastName(QString lastName)
{
    set("lastName", lastName);
}

int Settings::weekCount(Month::Months month)
{
    return m_weekCount.value(month);
}

QPair<int, int> Settings::weekDate(int week)
{
    return m_weeksDays.value(week);
}

int Settings::secondSemesterWeek()
{
    return get<int>("secondSemester", 22);
}
