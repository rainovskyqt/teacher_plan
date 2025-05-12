#ifndef PAGETOTAL_H
#define PAGETOTAL_H

#include "printpage.h"

#include <database/models/plantime.h>
#include <database/models/datamodels.h>

class PrintTotalData;

class PageTotal : public PrintPage
{
    Q_OBJECT
public:
    PageTotal(int wigth, int height, int coefficient, PagePosition position, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;

    PrintTotalData *m_printData;

    QRect m_rate;
    QRect m_title;
    QRect m_numberTitle;
    QRect m_number_I;
    QRect m_number_II;
    QRect m_number_III;
    QRect m_number_IV;
    QRect m_number_V;
    QRect m_workTitle;
    QRect m_workStudy;
    QRect m_workMethod;
    QRect m_workResearch;
    QRect m_workSport;
    QRect m_workOther;
    QRect m_workTotal;
    QRect m_semestrTitle;
    QRect m_semestrTitle_I;
    QRect m_semestrTitle_II;
    QRect m_yearTitle;
    QRect m_workStudy_I;
    QRect m_workMethod_I;
    QRect m_workResearch_I;
    QRect m_workSport_I;
    QRect m_workOther_I;
    QRect m_workTotal_I;
    QRect m_workStudy_II;
    QRect m_workMethod_II;
    QRect m_workResearch_II;
    QRect m_workSport_II;
    QRect m_workOther_II;
    QRect m_workTotal_II;
    QRect m_workStudy_year;
    QRect m_workMethod_year;
    QRect m_workResearch_year;
    QRect m_workSport_year;
    QRect m_workOther_year;
    QRect m_workTotal_year;
    QRect m_protocolTitle;
    QRect m_protocolNumber;

    int getTotalTime();
    int getTotalTime(PlanTime::Semester s);
    int getTotalTime(WorkType type);

protected:
    void setRects() override;
};

#endif // PAGETOTAL_H
