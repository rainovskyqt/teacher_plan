#include "pagecomplete.h"

#include <QPainter>

#include <database/database.h>
#include<QMultiMap>

#include <misc/month.h>

PageComplete::PageComplete(int wigth, int height, int coefficient, PagePosition position, int part, QWidget *parent) :
    PrintPage(wigth, height, coefficient, position, part, parent)
{
}

void PageComplete::setData(PrintData *data)
{
    m_data = qobject_cast<PrintComplite*>(data);
}

void PageComplete::paintData(QPainter &painter)
{
    painter.setFont(m_fontMainBold);
    painter.drawText(m_title, Qt::AlignCenter, QString("ВЫПОЛНЕНИЕ УЧЕБНОЙ НАГРУЗКИ В ТЕЧЕНИИ %1 - %2 УЧЕБНОГО ГОДА")
                                                   .arg("2024", "2025"));

    painter.setFont(m_fontMain);
    painter.drawText(m_totalHourses, Qt::AlignLeft, QString("Учебная годовая нагрузка %1 час.")
                                                        .arg(m_data->totalHours()));

    drawCell(&painter, m_startCell);
    drawRowNames(painter);
    drawColumnNames(painter);
    drawValues(painter);


    painter.drawText(m_comments, Qt::AlignJustify|Qt::TextWordWrap, QString("Примечание:\n%1")
                                                                          .arg(m_data->comments()));
}

void PageComplete::drawRowNames(QPainter &painter)
{
    int offset = 0;
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other){
            i = Month::January;                //Если перешли за декабрь, ставим январь
        }

        drawCell(&painter, QRect(m_startCell.left(), m_startCell.bottom() + singleRow() * offset, m_startCell.width(), singleRow()),
                 Qt::AlignLeft|Qt::AlignVCenter, Month().name((Month::Months)i));
        ++offset;

        if(i == Month::January){
            drawCell(&painter, QRect(m_startCell.left(), m_startCell.bottom() + singleRow() * offset, m_startCell.width(), singleRow()),
                     Qt::AlignLeft|Qt::AlignVCenter, "Итого за\nсеместр", 0.8);
            ++offset;
        }
    }

    drawCell(&painter, QRect(m_startCell.left(), m_startCell.bottom() + singleRow() * offset, m_startCell.width(), singleRow()),
             Qt::AlignLeft|Qt::AlignVCenter, "Итого за\nсеместр", 0.8);

    drawCell(&painter, QRect(m_startCell.left(), m_startCell.bottom() + singleRow() * ++offset, m_startCell.width(), singleRow()),
             Qt::AlignLeft|Qt::AlignVCenter, "ВСЕГО:");

    m_comments.setTop(m_startCell.bottom() + singleRow() * ++offset + singleRow());
}

void PageComplete::drawColumnNames(QPainter &painter)
{
    drawCell(&painter, m_tableHeader, Qt::AlignCenter, "Количество часов по разделам работы, включаемых в учебную нагрузку");

    auto workTypes = Database::get()->getDictionary(Database::WorkForm);

    m_cellWigth = (m_tableHeader.width() / (workTypes.count() + 1)) + 1;


    for(int column = 0; column < workTypes.count(); ++column){
        drawCell(&painter, QRect(m_tableHeader.left() + m_cellWigth * column, m_tableHeader.bottom() + 1, m_cellWigth, singleRow() * 4),
                 Qt::AlignCenter|Qt::TextWordWrap, workTypes.at(column).name(), 1.0, true);
    }

    auto r = QRect(m_tableHeader.left() + m_cellWigth * workTypes.count(), m_tableHeader.bottom() + 1, m_cellWigth - 6, singleRow() * 4);
    r.setCoords(r.left(), r.top(), m_tableHeader.right(), r.bottom());
    drawCell(&painter, r, Qt::AlignCenter|Qt::TextWordWrap, "Всего\nчасов", 1.0, true);
}

void PageComplete::drawValues(QPainter &painter)
{
    auto values = m_data->values();
    int col = 0;

    for(auto it = values.begin(); it != values.end(); ++it){
        auto val = it.value();

        auto r = QRect(m_startCell.right() + m_cellWigth * val.first,
                       m_startCell.bottom() + m_cellHeigth * it.key(),
                       m_cellWigth, m_cellHeigth);

        if(it.value().first == 16)
            r.setCoords(r.left(),r.top(), m_tableHeader.right(), r.bottom());
        drawCell(&painter, r,Qt::AlignCenter,  it.value().second, 0.9);
    }

}

void PageComplete::setRects()
{
    m_title = QRect(m_leftBord, point(5), m_rigthBord, singleRow());
    m_totalHourses = QRect(m_leftBord, m_title.bottom(), m_rigthBord, singleRow());
    m_startCell = QRect(m_leftBord - point(5), m_totalHourses.bottom(), point(17), singleRow() *5);
    m_tableHeader = QRect(m_startCell.right(), m_startCell.top(), m_rigthBord - point(10), singleRow());
    m_comments = QRect(m_leftBord, 0, m_rigthBord - point(5), m_bottomBord);

    m_cellHeigth = singleRow();
}
