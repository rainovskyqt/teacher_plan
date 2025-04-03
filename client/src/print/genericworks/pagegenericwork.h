#ifndef PAGEGENERICWORK_H
#define PAGETGENERICWORK_H

#include "print/printpage.h"

#include "print/datafiles/printgenericwork.h"

class PageGenericWork : public PrintPage
{
    Q_OBJECT
public:
    PageGenericWork(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:

    QRect m_approved;
    QRect m_approvedUser;

    PrintGenericWork *m_data;

    void paintData(QPainter &painter) override;



protected:
    void setRects() override;
};

#endif // PAGEGENERICWORK_H
