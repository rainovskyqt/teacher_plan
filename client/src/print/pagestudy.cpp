#include "pagestudy.h"

#include <QPainter>

PageStudy::PageStudy(int wigth, int height, int coefficient, QWidget *parent) :
    PrintPage(wigth, height, coefficient, parent)
{
}

void PageStudy::setData(PrintData *data)
{
    Q_UNUSED(data)
}

void PageStudy::paintData(QPainter &painter)
{
    painter.setFont(m_fontMainBold);

    drawCell(&painter, m_workTitle, Qt::AlignLeft, "I. УЧЕБНАЯ РАБОТА");
    drawCell(&painter, m_month1, Qt::AlignCenter, "1");
    drawCell(&painter, m_month2, Qt::AlignCenter, "2");;
    drawCell(&painter, m_month3, Qt::AlignCenter, "3");
    drawCell(&painter, m_month4, Qt::AlignCenter, "4");
    drawCell(&painter, m_month5, Qt::AlignCenter, "5");
    drawCell(&painter, m_totalTitle, Qt::AlignCenter, "I\nполугодие", 0.8);
    drawCell(&painter, m_commentsTitle, Qt::AlignCenter, "Примечание");

    drawCell(&painter, m_positionTitle, Qt::AlignCenter, "№\n п/п", 0.8);
    drawCell(&painter, m_workNameTitle, Qt::AlignCenter|Qt::TextWordWrap, "Наименование дисциплины, курс, группа. Виды работ", 0.8);
    drawCell(&painter, m_hoursTypeTitle, Qt::AlignCenter, "");

    drawCell(&painter, m_weekStartTitle, Qt::AlignCenter, "12", 0.8);

    QRect h = QRect(m_hoursTypeTitle.right() + 1, m_weekStartTitle.bottom() + 1, point(5) - 1, (singleRow() * 2) / 3);
    drawCell(&painter, h, Qt::AlignCenter, "19", 0.8);
    QRect g = QRect(m_hoursTypeTitle.right() + 1, h.bottom() + 1, point(5) - 1, (singleRow() * 2) / 3);
    drawCell(&painter, g, Qt::AlignCenter, "52", 0.8);
}

void PageStudy::setRects()
{
    m_workTitle = QRect(m_leftBord, m_topBord, point(100), singleRow());
    m_month1 = QRect(m_workTitle.right() + 1, m_workTitle.top(), point(20), singleRow());
    m_month2 = QRect(m_month1.right() + 1, m_workTitle.top(), point(20), singleRow());
    m_month3 = QRect(m_month2.right() + 1, m_workTitle.top(), point(20), singleRow());
    m_month4 = QRect(m_month3.right() + 1, m_workTitle.top(), point(20), singleRow());
    m_month5 = QRect(m_month4.right() + 1, m_workTitle.top(), point(20), singleRow());
    m_totalTitle = QRect(m_month5.right() + 1, m_workTitle.top(), point(17), singleRow() * 2);
    m_commentsTitle = QRect(m_totalTitle.right() + 1, m_workTitle.top(), point(60), singleRow() * 3);

    m_positionTitle = QRect(m_workTitle.left(), m_workTitle.bottom() + 1, point(5), singleRow() * 2);
    m_workNameTitle = QRect(m_positionTitle.right() + 1, m_workTitle.bottom() + 1, point(85), singleRow() * 2);
    m_hoursTypeTitle = QRect(m_workNameTitle.right() + 1, m_workTitle.bottom() + 1, point(10), singleRow() * 2);

    m_weekStartTitle = QRect(m_hoursTypeTitle.right() + 1, m_workTitle.bottom() + 1, point(5) - 1, (singleRow() * 2) / 3);
}

