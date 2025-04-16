#ifndef PAGEGENERICWORK_H
#define PAGEGENERICWORK_H

#include "print/printpage.h"

#include "print/datafiles/printgenericdata.h"

class PageGenericWork : public PrintPage
{
    Q_OBJECT

public:
    PageGenericWork(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:

    QRect m_approved;
    QRect m_approvedUser;
    QRect m_title;
    QRect m_semester;
    QRect m_hoursTitle;
    QRect m_planeTitle;
    QRect m_factTitle;
    QRect m_commentsTitle;

    QRect m_position;
    QRect m_name;
    QRect m_plane;
    QRect m_fact;
    QRect m_comments;
    QRect m_signTeacher;
    QRect m_signBoss;


    PrintGenericData *m_data;

    void paintData(QPainter &painter) override;

protected:
    void setRects() override;
};

#endif // PAGEGENERICWORK_H
