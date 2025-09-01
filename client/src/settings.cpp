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
        {1, qMakePair(1, 7)},
        {2, qMakePair(8, 14)},
        {3, qMakePair(15, 21)},
        {4, qMakePair(22, 28)},
        {5, qMakePair(29, 5)},
        {6, qMakePair(6, 12)},
        {7, qMakePair(13, 19)},
        {8, qMakePair(20, 26)},
        {9, qMakePair(27, 2)},
        {10, qMakePair(3, 9)},
        {11, qMakePair(10, 16)},
        {12, qMakePair(17, 23)},
        {13, qMakePair(24, 30)},
        {14, qMakePair(1, 7)},
        {15, qMakePair(8, 14)},
        {16, qMakePair(15, 21)},
        {17, qMakePair(22, 28)},
        {18, qMakePair(29, 4)},
        {19, qMakePair(5, 11)},
        {20, qMakePair(12, 18)},
        {21, qMakePair(19, 25)},
        {22, qMakePair(26, 1)},
        {23, qMakePair(2, 8)},
        {24, qMakePair(9, 15)},
        {25, qMakePair(16, 22)},
        {26, qMakePair(23, 1)},
        {27, qMakePair(2, 8)},
        {28, qMakePair(9, 15)},
        {29, qMakePair(16, 22)},
        {30, qMakePair(23, 29)},
        {31, qMakePair(30, 5)},
        {32, qMakePair(6, 12)},
        {33, qMakePair(13, 19)},
        {34, qMakePair(20, 26)},
        {35, qMakePair(29, 3)},
        {36, qMakePair(4, 10)},
        {37, qMakePair(11, 17)},
        {38, qMakePair(18, 24)},
        {39, qMakePair(25, 31)},
        {40, qMakePair(1, 7)},
        {41, qMakePair(8, 14)},
        {42, qMakePair(15, 21)},
        {43, qMakePair(22, 28)},
        {44, qMakePair(29, 5)},
    };
}

Settings Settings::get()
{
    return Settings();
}

QString Settings::dbHost()
{
    return get<QString>("dbHost", "10.0.2.18");
    // return get<QString>("dbHost", "127.0.0.1");
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

int Settings::maxLandscapeWorkRowCount()
{
    return get<int>("maxLandscapeWorkRowCount", 15);
}

int Settings::maxPortraitWorkRowCount()
{
    return get<int>("maxPortraitWorkRowCount", 21);
}
