#ifndef PAGERESEARCHINGWORK_H
#define PAGERESEARCHINGWORK_H

#include "pagegenericwork.h"

class PageResearchingWork : public PageGenericWork
{
    Q_OBJECT

public:
    PageResearchingWork(int wigth, int height, int coefficient, QWidget *parent = nullptr);
};

#endif // PAGERESEARCHINGWORK_H
