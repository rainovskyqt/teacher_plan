#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

Database::Database(){}

Database *Database::instance()
{
    static Database base;
    return &base;
}

void Database::init() // TODO setup
{
    m_base = QSqlDatabase::addDatabase("QMYSQL");
    m_base.setDatabaseName("ordo_dev");
    m_base.setHostName("10.0.2.18");
    m_base.setUserName("ordo");
    m_base.setPassword("ordo7532159");
}

QVector<PlanTime *> Database::getTotaTimeList() // TODO из базы
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
    QByteArray hashPass = QCryptographicHash::hash(password.toUtf8(),
                                                   QCryptographicHash::Sha256).toHex();

    int id = 0;

    QString queryStr = "SELECT id FROM user WHERE login = :login AND password = :password";
    QVariantMap args;
    args.insert(":login", login);
    args.insert(":password", hashPass);

    QSqlQuery *query = makeQuery(queryStr, args);

    if(query->next())
        id = query->value("id").toInt();

    emit logged(id);

    delete query;
}

QMap<int, QString> Database::dictionary(Dictionary name)
{
    QString tableName;

    switch (name) {
    case Department: tableName = "department"; break;
    case Post: tableName = "post"; break;
    }

    QString queryStr = QString("SELECT id, name FROM %1").arg(tableName);
    QSqlQuery *query = makeQuery(queryStr);

    QMap<int, QString> dictionary;
    while (query->next()) {
        dictionary.insert(query->value("id").toInt(), query->value("name").toString());
    }

    delete query;

    return dictionary;
}

QSqlQuery *Database::makeQuery(QString queryStr, QVariantMap args)
{
    m_base.open();

    QSqlQuery *query = new QSqlQuery(m_base);
    query->prepare(queryStr);
    for(QVariantMap::iterator it = args.begin(); it != args.end(); ++it)
        query->bindValue(it.key(), it.value());

    if(query->exec()){
        qDebug()<<query->lastError().text();
    }

    m_base.close();

    return query;
}
