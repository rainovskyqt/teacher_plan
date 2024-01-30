#include "database.h"

Database &Database::instance()
{
    static Database base;
    return base;
}

TotalTimeList *Database::getTotaTimeList()
{
    return new TotalTimeList();
}

Database::Database()
{

}
