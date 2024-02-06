#include "database.h"

#include <QJsonObject>

Database *Database::instance()
{
    static Database base;
    return &base;
}

void Database::init(QString host, int port)
{
    m_serverUrl.setScheme("http");
    m_serverUrl.setHost(host);
    m_serverUrl.setPort(port);
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

void Database::login(QString login, QString password)
{
    QJsonObject params;
    params.insert("login", login);
    params.insert("password", password);
}

Database::Database()
{

}
