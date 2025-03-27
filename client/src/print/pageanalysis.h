#ifndef PAGEANALYSIS_H
#define PAGEANALYSIS_H

#include "printpage.h"

class PageAnalysis : public PrintPage
{
    Q_OBJECT
public:
    explicit PageAnalysis(int wigth, int height, int coefficient, int semester, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;

    QRect m_title;
    QRect m_half;
    QRect m_teacherSign;
    QRect m_cheefTitle;
    QRect m_cheefSign;
    QRect m_protocol;

protected:
    void setRects() override;
};

#endif // PAGEANALYSIS_H
