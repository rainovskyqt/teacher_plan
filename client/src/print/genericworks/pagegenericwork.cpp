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
    drawCell(&painter, m_planeTitle, Qt::AlignCenter, "План", 0.9);
    drawCell(&painter, m_factTitle, Qt::AlignCenter, "Факт", 0.9);
    drawCell(&painter, m_commentsTitle, Qt::AlignCenter|Qt::TextWordWrap, "Отметка о выполнении с указанием сроков "
                                                                            "проведенеия и реквизитов подтверждающих документов ", 0.5);

    drawCell(&painter, m_semester, Qt::AlignCenter, m_data->isSecond() ? "ВТОРОЕ ПОЛУГОДИЕ" : "ПЕРВОЕ ПОЛУГОДИЕ");

    auto const works = m_data->works();

    int bottom = 0;

    for(auto const w: works){
        drawCell(&painter, QRect(m_position.x(), m_position.y() + bottom, m_position.width(), m_position.height()), Qt::AlignCenter, QString::number(w->number()));
        drawCell(&painter, QRect(m_name.x(), m_name.y() + bottom, m_name.width(), m_name.height()), Qt::AlignJustify|Qt::TextWordWrap, w->name(), 0.8);
        drawCell(&painter, QRect(m_plane.x(), m_plane.y() + bottom, m_plane.width(), m_plane.height()), Qt::AlignCenter|Qt::TextWordWrap, QString::number(w->plane()));
        drawCell(&painter, QRect(m_fact.x(), m_fact.y() + bottom, m_fact.width(), m_fact.height()), Qt::AlignCenter|Qt::TextWordWrap, QString::number(w->fact()));
        drawCell(&painter, QRect(m_comments.x(), m_comments.y() + bottom, m_comments.width(), m_comments.height()), Qt::AlignJustify|Qt::TextWordWrap, w->getComments(), 0.8);
        bottom += m_position.height();
    }

    drawCell(&painter, QRect(m_position.x(), m_position.y() + bottom, m_position.width() + m_name.width(), m_position.height()), Qt::AlignRight, "Всего часов:");
    drawCell(&painter, QRect(m_plane.x(), m_plane.y() + bottom, m_plane.width(), m_plane.height()), Qt::AlignCenter|Qt::TextWordWrap, QString::number(m_data->totalPlane()));
    drawCell(&painter, QRect(m_fact.x(), m_fact.y() + bottom, m_fact.width(), m_fact.height()), Qt::AlignCenter|Qt::TextWordWrap, QString::number(m_data->totalFact()));
    drawCell(&painter, QRect(m_comments.x(), m_comments.y() + bottom, m_comments.width(), m_comments.height()), Qt::AlignJustify|Qt::TextWordWrap, "");
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
    m_planeTitle = QRect(m_title.right() + 1, m_hoursTitle.bottom() + 2, point(10), singleRow() / 2);
    m_factTitle = QRect(m_title.right() + point(10) + 1, m_hoursTitle.bottom() + 2, point(10), singleRow() / 2);
    m_commentsTitle = QRect(m_title.right() + point(20) + 1, m_title.top(), point(45), singleRow());
    m_semester = QRect(m_leftBord, m_title.bottom() + 1, m_rigthBord + point(5), singleRow());

    m_position = QRect(m_title.left(), m_semester.bottom() + 1, point(5), singleRow() * 1.2);
    m_name = QRect(m_position.right() + 1, m_position.top(), m_title.width() - m_position.width(), singleRow() * 1.2);
    m_plane = QRect(m_planeTitle.left(), m_semester.bottom() + 1, m_planeTitle.width(), singleRow() * 1.2);
    m_fact = QRect(m_factTitle.left(), m_semester.bottom() + 1, m_factTitle.width(), singleRow() * 1.2);
    m_comments = QRect(m_commentsTitle.left(), m_semester.bottom() + 1, m_commentsTitle.width(), singleRow() * 1.2);
}
