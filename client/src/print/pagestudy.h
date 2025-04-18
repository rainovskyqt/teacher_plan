#ifndef PAGESTUDY_H
#define PAGESTUDY_H

#include "printpage.h"

class PageStudy : public PrintPage
{
    Q_OBJECT
public:
    explicit PageStudy(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;


    QRect m_workTitle;
    QRect m_month1;
    QRect m_month2;
    QRect m_month3;
    QRect m_month4;
    QRect m_month5;
    QRect m_totalTitle;
    QRect m_commentsTitle;

    QRect m_positionTitle;
    QRect m_workNameTitle;
    QRect m_hoursTypeTitle;

    QRect m_weekStartTitle;

protected:
    void setRects() override;

};

#endif // PAGESTUDY_H
