#ifndef PAGESPORTWORK_H
#define PAGESPORTWORK_H

#include "pagegenericwork.h"

class PageSportWork : public PageGenericWork
{
    Q_OBJECT

public:
    PageSportWork(int wigth, int height, int coefficient, PagePosition position, QWidget *parent = nullptr);
};

#endif // PAGESPORTWORK_H
