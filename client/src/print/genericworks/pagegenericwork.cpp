#include "pagegenericwork.h"

#include <QPainter>

PageGenericWork::PageGenericWork(int wigth, int height, int coefficient, QWidget *parent) :
    PrintPage(wigth, height, coefficient, parent)
{
}

void PageGenericWork::setData(PrintData *data)
{
    m_data = qobject_cast<PrintGenericData*>(data);
}

void PageGenericWork::paintData(QPainter &painter)
{
    painter.setFont(m_fontMain);

    painter.drawText(m_approved, "СОГЛАСОВАНО");
    painter.drawText(m_approvedUser, QString("%1\n"
                                     "________________ %2\n"
                                     "\"_____\" _______________ 20___г.")
                     .arg(m_data->approvedPost(), m_data->approvedUser())
                     );

    drawCell(&painter, m_title, Qt::AlignLeft, m_data->workName());
    drawCell(&painter, m_hoursTitle, Qt::AlignCenter, "Кол-во часов", 0.9);
    drawCell(&painter, m_plane, Qt::AlignCenter, "План", 0.9);
    drawCell(&painter, m_fact, Qt::AlignCenter, "Факт", 0.9);
    drawCell(&painter, m_comments, Qt::AlignCenter|Qt::TextWordWrap, "Отметка о выполнении с указанием сроков "
                                                                   "проведенеия и реквизитов подтверждающих документов ", 0.5);

    drawCell(&painter, m_semester, Qt::AlignCenter, m_data->isSecond() ? "ВТОРОЕ ПОЛУГОДИЕ" : "ПЕРВОЕ ПОЛУГОДИЕ");
}

void PageGenericWork::setRects()
{
    m_approved = QRect(point(110), m_topBord, m_rigthBord - point(110), 0);
    if(!m_data->approvedUser().isEmpty() && !m_data->isSecond()){
        m_approved.setHeight(singleRow());
    }

    m_approvedUser = QRect(m_approved.left(), m_approved.bottom(), m_wigth, 0);
    if(!m_data->approvedUser().isEmpty() && !m_data->isSecond())
        m_approvedUser.setHeight(singleRow() * 4.5);

    m_title = QRect(m_leftBord, m_approvedUser.bottom(), point(130), singleRow());
    m_hoursTitle = QRect(m_title.right() + 1, m_title.top(), point(20), singleRow() / 2);
    m_plane = QRect(m_title.right() + 1, m_hoursTitle.bottom() + 2, point(10), singleRow() / 2);
    m_fact = QRect(m_title.right() + point(10) + 1, m_hoursTitle.bottom() + 2, point(10), singleRow() / 2);
    m_comments = QRect(m_title.right() + point(20) + 1, m_title.top(), point(45), singleRow());
    m_semester = QRect(m_leftBord, m_title.bottom() + 1, m_rigthBord + point(5), singleRow());

}
