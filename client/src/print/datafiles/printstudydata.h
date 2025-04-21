#ifndef PRINTSTUDYDATA_H
#define PRINTSTUDYDATA_H

#include "printdata.h"

class PrintStudyData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintStudyData(QObject *parent = nullptr);

};

#endif // PRINTSTUDYDATA_H
