#ifndef PAGEMETHODICWORK_H
#define PAGEMETHODICWORK_H

#include "pagegenericwork.h"

class PageMethodicWork : public PageGenericWork
{
    Q_OBJECT
public:
    PageMethodicWork(int wigth, int height, int coefficient, PagePosition position, QWidget *parent = nullptr);
};

#endif // PAGEMETHODICWORK_H
