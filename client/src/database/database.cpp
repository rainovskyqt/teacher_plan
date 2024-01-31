#include "database.h"

Database &Database::instance()
{
    static Database base;
    return base;
}

QVector<PlanTime *> Database::getTotaTimeList()
{
    QVector<PlanTime *> hours;
    hours.append(new PlanTime("I.", "Учебная работа", 0, 0));
    hours.append(new PlanTime("II.", "Учебно-методическая работа", 0, 0));
    hours.append(new PlanTime("III.", "Научно-исследовательская работа", 0, 0));
    hours.append(new PlanTime("IV.", "Воспитательная и спортивная работа", 0, 0));
    hours.append(new PlanTime("V.", "Другие виды работ", 0, 0));

    return hours;
}

Database::Database()
{

}
