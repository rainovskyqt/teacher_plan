#ifndef PRINTTOTALDATA_H
#define PRINTTOTALDATA_H

#include "printdata.h"
#include "database/models/plantime.h"
#include "database/models/datamodels.h"

class PrintTotalData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintTotalData(QObject *parent = nullptr);

    QString rate() const;
    void setRate(const QString &newRate);

    void setTime(WorkType type, PlanTime::Semester semester, int val);
    int getTime(WorkType type, PlanTime::Semester semester);

private:
    QString m_rate;

    QMap<WorkType, QPair<int, int>> m_times;
};

#endif // PRINTTOTALDATA_H
