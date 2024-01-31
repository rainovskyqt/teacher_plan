#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "totaltime/plantime.h"
#include <QVector>

class Database : public QObject
{
    Q_OBJECT

public:
    static Database &instance();

    QVector<PlanTime*> getTotaTimeList();


signals:

private:
     explicit Database();
};

#endif // DATABASE_H
