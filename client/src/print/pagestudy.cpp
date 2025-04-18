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
}

void PageStudy::setRects()
{
}

