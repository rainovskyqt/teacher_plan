#include "pagecomplete.h"

#include <QPainter>

#include <database/database.h>
#include<QMultiMap>

#include <misc/month.h>

PageComplete::PageComplete(int wigth, int height, int coefficient, PagePosition position, QWidget *parent) :
    PrintPage(wigth, height, coefficient, position, parent)
{
}

void PageComplete::setData(PrintData *data)
{
    m_data = qobject_cast<PrintComplite*>(data);
}

void PageComplete::paintData(QPainter &painter)
{
    painter.setFont(m_fontMainBold);

    m_currentCell = m_title;

    painter.drawText(m_currentCell, Qt::AlignCenter, QString("ВЫПОЛНЕНИЕ УЧЕБНОЙ НАГРУЗКИ В ТЕЧЕНИИ %1 - %2 УЧЕБНОГО ГОДА")
                                                   .arg("2024", "2025"));

    painter.setFont(m_fontMain);

    m_currentCell = m_totalHourses;
    painter.drawText(m_currentCell, Qt::AlignLeft, QString("Учебная годовая нагрузка %1 час.")
                                                        .arg(m_data->totalHours()));

    m_currentCell = m_startCell;
    drawCell(&painter, m_startCell);
    drawRowNames(painter);
    drawColumnNames(painter);
    // drawValues(painter);


    // painter.drawText(m_comments, Qt::AlignJustify|Qt::TextWordWrap, QString("Примечание:\n%1")
    //                                                                       .arg(m_data->comments()));
}

void PageComplete::drawRowNames(QPainter &painter)
{
    m_currentCell.moveLeft(m_startCell.left());

    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other){
            i = Month::January;                //Если перешли за декабрь, ставим январь
        }

        m_currentCell.moveTop(m_currentCell.bottom() + 1);
        m_currentCell.setHeight(singleRow() * 1.2);

        drawCell(&painter, m_currentCell, Qt::AlignCenter, Month().name((Month::Months)i));

        if(i == Month::January){
            m_currentCell.moveTop(m_currentCell.bottom() + 1);
            drawCell(&painter, m_currentCell, Qt::AlignCenter, "Итого за\nсеместр", 0.8, 0.6);
        }
    }
    m_currentCell.moveTop(m_currentCell.bottom() + 1);
    drawCell(&painter, m_currentCell,Qt::AlignCenter, "Итого за\nсеместр", 0.8, 0.6);

    m_currentCell.moveTop(m_currentCell.bottom() + 1);
    drawCell(&painter, m_currentCell, Qt::AlignCenter, "ВСЕГО:");

    // m_comments.setTop(m_startCell.bottom() + singleRow() * ++offset + singleRow());
}

void PageComplete::drawColumnNames(QPainter &painter)
{
    m_currentCell = m_tableHeader;
    drawCell(&painter, m_currentCell, Qt::AlignCenter, "Количество часов по разделам работы, включаемых в учебную нагрузку");

    auto workTypes = Database::get()->getDictionary(Database::WorkForm);

    m_currentCell.setWidth(m_tableHeader.width() / (workTypes.count() + 1) + 2);
    m_currentCell.moveTop(m_currentCell.bottom() + 1);

    m_currentCell.setHeight(m_startCell.height() - m_currentCell.height());

    for(int column = 0; column < workTypes.count(); ++column){
        drawCell(&painter, m_currentCell, Qt::AlignCenter, workTypes.at(column).name(), 0.9, 1.0, true);
        m_currentCell.moveLeft(m_currentCell.right() + 1);
    }

    m_currentCell.setWidth(m_tableHeader.right() - m_currentCell.right());
    m_currentCell.setCoords(m_currentCell.left(), m_currentCell.top(), m_tableHeader.right(), m_currentCell.bottom());
    drawCell(&painter, m_currentCell, Qt::AlignCenter, "Всего часов", 0.9, 1.0, true);
}

void PageComplete::drawValues(QPainter &painter)
{
    auto values = m_data->values();

    for(auto it = values.begin(); it != values.end(); ++it){
        auto val = it.value();
        int offset = 0;
        if(it.value() == values.first())
            offset = 6;
        drawCell(&painter, QRect((m_startCell.right() + m_cellWigth * val.first) + 1,
                                 m_startCell.bottom() + m_cellHeigth * it.key(),
                                 m_cellWigth - offset, m_cellHeigth),
                 Qt::AlignCenter, it.value().second, 0.9);
    }

}

void PageComplete::setRects()
{
    m_title = QRect(m_leftBord, point(5), m_rigthBord, singleRow());
    m_totalHourses = QRect(m_leftBord, m_title.bottom(), m_rigthBord, singleRow());
    m_startCell = QRect(m_leftBord - point(5), m_totalHourses.bottom(), point(20), singleRow() *5);
    m_tableHeader = QRect(m_startCell.right() + 1, m_startCell.top(), m_rigthBord - point(10), singleRow());
    m_comments = QRect(m_leftBord, 0, m_rigthBord - point(5), m_bottomBord);

    m_cellHeigth = singleRow();
}
