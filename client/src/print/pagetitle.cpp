#include "pagetitle.h"
#include "datafiles/printtitledata.h"

#include <QPainter>

PageTitle::PageTitle(int wigth, int height, int coefficient, QWidget *parent) :
    PrintPage(wigth, height, coefficient, parent)
{
}

void PageTitle::setData(PrintData* data)
{
    m_printData = qobject_cast<PrintTitleData*>(data);
}

void PageTitle::paintData(QPainter &painter)
{
    painter.setFont(m_fontMain);
    painter.drawText(m_header, Qt::AlignCenter, "МИНИСТЕРСТВО СПОРТА РОССИЙСКОЙ ФЕДЕРАЦИИ"
                                                "\n\n"
                                                "Федеральное государственное бюджетное образовательное учреждение высшего образования\n"
                                                "\"ВОЛГОГРАДСКАЯ ГОСУДАРСТВЕННАЯ АКАДЕМИЯ ФИЗИЧЕСКОЙ КУЛЬТУРЫ\"\n"
                                                "(ФГБОУ ВО \"ВГАФК\")");

    painter.setFont(m_fontTitle);
    painter.drawText(m_title, Qt::AlignCenter, "ИНДИВИДУАЛЬНЫЙ ПЛАН");

    painter.setFont(m_fontMain);
    painter.drawText(m_year, Qt::AlignCenter, QString("на %1 - %2 учебный год").arg(m_printData->startYear()).arg(m_printData->endYear()));
    painter.drawText(m_office, Qt::AlignLeft, QString("Кафедра: %1").arg(m_printData->office()));
    painter.drawText(m_teacherName, Qt::AlignLeft, QString("Фамилия, имя, отчество: %1").arg(m_printData->fio()));
    painter.drawText(m_teacherPost, Qt::AlignLeft, QString("Должность, ученое звание, степень: %1").arg(m_printData->post()));
}

void PageTitle::setRects()
{
    m_header = QRect(m_leftBord, point(15), m_rigthBord, singleRow() * 4.5);
    m_approved = QRect(point(110), m_header.bottom() + point(20), m_wigth, singleRow() * 1.5);
    m_approvedUser = QRect(m_approved.left(), m_approved.bottom(), m_wigth, singleRow() * 4.5);
    m_title = QRect(m_leftBord, m_approvedUser.bottom() + point(25), m_rigthBord, singleRow());
    m_year = QRect(m_title.left(), m_title.bottom() + point(5), m_title.right(), singleRow());
    m_office = QRect(m_leftBord, m_year.bottom() + point(15), m_rigthBord, singleRow());
    m_teacherName = QRect(m_leftBord, m_office.bottom() + point(15), m_rigthBord, singleRow());
    m_teacherPost = QRect(m_leftBord, m_teacherName.bottom() + point(15), m_rigthBord, singleRow());
}
