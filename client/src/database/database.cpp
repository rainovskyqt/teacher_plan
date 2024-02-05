#include "database.h"

Database &Database::instance()
{
    static Database base;
    return base;
}

QVector<PlanTime *> Database::getTotaTimeList()
{
    QVector<PlanTime *> hours;
    hours.append(new PlanTime(1, "Учебная работа", 0, 0));
    hours.append(new PlanTime(2, "Учебно-методическая работа", 0, 0));
    hours.append(new PlanTime(3, "Научно-исследовательская работа", 0, 0));
    hours.append(new PlanTime(4, "Воспитательная и спортивная работа", 0, 0));
    hours.append(new PlanTime(5, "Другие виды работ", 0, 0));

    return hours;
}

Database::Database()
{

}
