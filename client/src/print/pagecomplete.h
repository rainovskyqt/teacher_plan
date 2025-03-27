#ifndef PAGECOMPLETE_H
#define PAGECOMPLETE_H

#include "printpage.h"

class PageComplete : public PrintPage
{
    Q_OBJECT
public:
    PageComplete(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;

    QRect m_title;
    QRect m_totalHourses;
    QRect m_startCell;
    QRect m_tableHeader;
    QRect m_comments;

    void drawRowNames(QPainter &painter);
    void drawColumnNames(QPainter &painter);

protected:
    void setRects() override;
};

#endif // PAGECOMPLETE_H
