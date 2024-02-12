#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "totaltime/plantime.h"
#include <QVector>
#include <QSqlDatabase>
#include <QVariantMap>
#include <QMap>

class Database : public QObject
{
    Q_OBJECT

public:

    enum Dictionary{
        Department,
        Post
    };

    static Database *instance();
    void init();
    QVector<PlanTime*> getTotaTimeList();

    void login(QString login, QString password);
    QMap<int, QString> dictionary(Dictionary name);

public slots:

signals:
    void logged(int);

private:
    explicit Database();

    QSqlDatabase m_base;

    QSqlQuery *makeQuery(QString queryStr, QVariantMap args = QVariantMap());
};

#endif // DATABASE_H
