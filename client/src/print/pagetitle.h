#ifndef PAGETITLE_H
#define PAGETITLE_H

#include "printpage.h"
#include "printdata.h"

class PageTitle : public PrintPage
{
    Q_OBJECT
public:
    explicit PageTitle(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;

    QRect m_header;
    QRect m_approved;
    QRect m_approvedUser;
    QRect m_title;
    QRect m_year;
    QRect m_office;
    QRect m_teacherName;
    QRect m_teacherPost;

    PrintTitleData* m_titleData;

protected:
    void setRects() override;
};

#endif // PAGETITLE_H
