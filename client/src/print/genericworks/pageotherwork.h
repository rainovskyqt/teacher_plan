#ifndef PAGEOTHERWORK_H
#define PAGEOTHERWORK_H

#include "pagegenericwork.h"

class PageOtherWork : public PageGenericWork
{
    Q_OBJECT

public:
    PageOtherWork(int wigth, int height, int coefficient, QWidget *parent = nullptr);
};

#endif // PAGEOTHERWORK_H
