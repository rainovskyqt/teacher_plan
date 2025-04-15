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
}

void PageGenericWork::setRects()
{
    m_approved = QRect(point(110), 0, m_rigthBord - point(110), 0);
    if(!m_data->approvedUser().isEmpty() && !m_data->isSecond()){
        m_approved.setY(m_topBord);
        m_approved.setHeight(singleRow());
    }

    m_approvedUser = QRect(m_approved.left(), m_approved.bottom(), m_wigth, 0);
    if(!m_data->approvedUser().isEmpty() && !m_data->isSecond())
        m_approvedUser.setHeight(singleRow() * 4.5);
}
