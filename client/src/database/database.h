#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "totaltime/totaltimelist.h"

class Database : public QObject
{
    Q_OBJECT

public:
    static Database &instance();

    TotalTimeList *getTotaTimeList();


signals:

private:
     explicit Database();
};

#endif // DATABASE_H
