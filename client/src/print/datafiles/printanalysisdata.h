#ifndef PRINTANALYSISDATA_H
#define PRINTANALYSISDATA_H

#include "printdata.h"

class PrintAnalysisData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintAnalysisData(QObject *parent = nullptr);
};

#endif // PRINTANALYSISDATA_H
