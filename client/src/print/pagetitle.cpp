#include "pagetitle.h"

#include <QPainter>

PageTitle::PageTitle(int wigth, int height, int coefficient, QWidget *parent) :
    PrintPage(wigth, height, coefficient, parent)
{
}

void PageTitle::setData(PrintData* data)
{
    m_titleData = qobject_cast<PrintTitleData*>(data);
}

void PageTitle::paintData(QPainter &painter)
{
    painter.setFont(m_fontMain);
    painter.drawText(m_header, Qt::AlignCenter, "МИНИСТЕРСТВО СПОРТА РОССИЙСКОЙ ФЕДЕРАЦИИ"
                                                "\n\n"
                                                "Федеральное государственное бюджетное образовательное учреждение высшего образования\n"
                                                "\"ВОЛГОГРАДСКАЯ ГОСУДАРСТВЕННАЯ АКАДЕМИЯ ФИЗИЧЕСКОЙ КУЛЬТУРЫ\"\n"
                                                "(ФГБОУ ВО \"ВГАФК\")");

    painter.drawText(m_approved, Qt::AlignLeft, "УТВЕРЖДАЮ");

    painter.drawText(m_approvedUser, Qt::AlignLeft, QString("Проректор по учебной работе\n"
                                                            "ФГБОУ ВО \"ВГАФК\"\n"
                                                            "_________________%1\n"
                                                            "\"____\"_______________ 20____г.").arg(m_titleData->studyRector()));

    painter.setFont(m_fontTitle);
    painter.drawText(m_title, Qt::AlignCenter, "ИНДИВИДУАЛЬНЫЙ ПЛАН");

    painter.setFont(m_fontMain);
    painter.drawText(m_year, Qt::AlignCenter, QString("на %1 - %2 учебный год").arg(m_titleData->startYear()).arg(m_titleData->endYear()));
    painter.drawText(m_office, Qt::AlignLeft, QString("Кафедра: %1").arg(m_titleData->office()));
    painter.drawText(m_teacherName, Qt::AlignLeft, QString("Фамилия, имя, отчество: %1").arg(m_titleData->fio()));
    painter.drawText(m_teacherPost, Qt::AlignLeft, QString("Должность, ученое звание, степень: %1").arg(m_titleData->post()));
}

void PageTitle::setRects()
{
    int leftBord = point(10);
    int rigthBord = m_wigth - point(10);

    m_header = QRect(leftBord, point(10), rigthBord, m_fontMain.pointSize() * 9);
    m_approved = QRect(point(130), m_header.bottom() + point(20), m_wigth, m_fontMain.pointSize() * 3);
    m_approvedUser = QRect(m_approved.left(), m_approved.bottom(), m_wigth, m_fontMain.pointSize() * 9);
    m_title = QRect(leftBord, m_approvedUser.bottom() + point(25), rigthBord, m_fontTitle.pointSize() * 2);
    m_year = QRect(m_title.left(), m_title.bottom() + point(5), m_title.right(), m_fontMain.pointSize() * 2);
    m_office = QRect(leftBord, m_year.bottom() + point(15), rigthBord, m_fontMain.pointSize() * 2);
    m_teacherName = QRect(leftBord, m_office.bottom() + point(15), rigthBord, m_fontMain.pointSize() * 2);
    m_teacherPost = QRect(leftBord, m_teacherName.bottom() + point(15), rigthBord, m_fontMain.pointSize() * 2);
}
