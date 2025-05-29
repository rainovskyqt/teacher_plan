#include "pagetotal.h"
#include "datafiles/printtotaldata.h"

#include <QPainter>

PageTotal::PageTotal(int wigth, int height, int coefficient, PagePosition position, int part, QWidget *parent) :
    PrintPage(wigth, height, coefficient, position, part, parent)
{}

void PageTotal::setData(PrintData *data)
{
    m_printData = qobject_cast<PrintTotalData*>(data);
}

void PageTotal::paintData(QPainter &painter)
{
    painter.setFont(m_fontMain);
    painter.drawText(m_rate, Qt::AlignLeft, QString("Доля занимаемой ставки: %1 ст.").arg(m_printData->rate()));
    painter.drawText(m_title, Qt::AlignCenter, "РАСПРЕДЕЛЕНИЕ ГОДОВОГО ОБЪЕМА ВРЕМЕНИ НА ОСНОВНЫЕ ВИДЫ РАБОТ");

    drawCell(&painter, m_numberTitle, Qt::AlignCenter, "№\nп/п");
    drawCell(&painter, m_number_I, Qt::AlignCenter, "I.");
    drawCell(&painter, m_number_II, Qt::AlignCenter, "II.");
    drawCell(&painter, m_number_III, Qt::AlignCenter, "III.");
    drawCell(&painter, m_number_IV, Qt::AlignCenter, "IV.");
    drawCell(&painter, m_number_V, Qt::AlignCenter, "V.");

    drawCell(&painter, m_workTitle, Qt::AlignCenter, "Наименование вида работ");
    drawCell(&painter, m_workStudy, Qt::AlignCenter, "Учебная работа");
    drawCell(&painter, m_workMethod, Qt::AlignCenter, "Учебно-методическая работа");
    drawCell(&painter, m_workResearch, Qt::AlignCenter, "Научно-исследовательская работа");
    drawCell(&painter, m_workSport, Qt::AlignCenter, "Воспитательная и спортивная работа");
    drawCell(&painter, m_workOther, Qt::AlignCenter, "Другие виды работ");
    drawCell(&painter, m_workTotal, Qt::AlignRight|Qt::AlignVCenter, "Всего за учебный год:   ");

    drawCell(&painter, m_semestrTitle, Qt::AlignCenter, "Плановое количество часов");
    drawCell(&painter, m_semestrTitle_I, Qt::AlignCenter, "I-е полугодие");
    drawCell(&painter, m_semestrTitle_II, Qt::AlignCenter, "II-е полугодие");
    drawCell(&painter, m_yearTitle, Qt::AlignCenter, "Всего за год");

    drawCell(&painter, m_workStudy_I, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::Educational, PlanTime::FirstSemester)));
    drawCell(&painter, m_workMethod_I, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::MethodicWork, PlanTime::FirstSemester)));
    drawCell(&painter, m_workResearch_I, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::ResearchingWork, PlanTime::FirstSemester)));
    drawCell(&painter, m_workSport_I, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::SportWork, PlanTime::FirstSemester)));
    drawCell(&painter, m_workOther_I, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::OtherWork, PlanTime::FirstSemester)));
    drawCell(&painter, m_workTotal_I, Qt::AlignCenter, QString::number(getTotalTime(PlanTime::FirstSemester)));

    drawCell(&painter, m_workStudy_II, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::Educational, PlanTime::SecondSemestr)));
    drawCell(&painter, m_workMethod_II, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::MethodicWork, PlanTime::SecondSemestr)));
    drawCell(&painter, m_workResearch_II, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::ResearchingWork, PlanTime::SecondSemestr)));
    drawCell(&painter, m_workSport_II, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::SportWork, PlanTime::SecondSemestr)));
    drawCell(&painter, m_workOther_II, Qt::AlignCenter, QString::number(m_printData->getTime(WorkType::OtherWork, PlanTime::SecondSemestr)));
    drawCell(&painter, m_workTotal_II, Qt::AlignCenter, QString::number(getTotalTime(PlanTime::SecondSemestr)));

    drawCell(&painter, m_workStudy_year, Qt::AlignCenter, QString::number(getTotalTime(WorkType::Educational)));
    drawCell(&painter, m_workMethod_year, Qt::AlignCenter, QString::number(getTotalTime(WorkType::MethodicWork)));
    drawCell(&painter, m_workResearch_year, Qt::AlignCenter, QString::number(getTotalTime(WorkType::ResearchingWork)));
    drawCell(&painter, m_workSport_year, Qt::AlignCenter, QString::number(getTotalTime(WorkType::SportWork)));
    drawCell(&painter, m_workOther_year, Qt::AlignCenter, QString::number(getTotalTime(WorkType::OtherWork)));
    drawCell(&painter, m_workTotal_year, Qt::AlignCenter, QString::number(getTotalTime()));

    painter.drawText(m_protocolTitle, Qt::AlignLeft, "Рассмотрено на заседании кафедры");
    painter.drawText(m_protocolNumber, Qt::AlignLeft, QString("Протокол № %1 от \" %2 \" %3 %4")
                                                          .arg("_____", "____", "________", "20___"));

}

int PageTotal::getTotalTime()
{
    int total = getTotalTime(PlanTime::FirstSemester) + getTotalTime(PlanTime::SecondSemestr);
    return total;
}

int PageTotal::getTotalTime(PlanTime::Semester s)
{
    int total = m_printData->getTime(WorkType::Educational, s) +
                m_printData->getTime(WorkType::MethodicWork, s) +
                m_printData->getTime(WorkType::ResearchingWork, s) +
                m_printData->getTime(WorkType::SportWork, s) +
                m_printData->getTime(WorkType::OtherWork, s);
    return total;
}

int PageTotal::getTotalTime(WorkType type)
{
    int total = m_printData->getTime(type, PlanTime::FirstSemester) +
                m_printData->getTime(type, PlanTime::SecondSemestr) ;
    return total;
}

void PageTotal::setRects()
{
    m_rate = QRect(m_leftBord, point(20), m_rigthBord, singleRow());
    m_title = QRect(m_leftBord, m_rate.bottom() + point(40), m_rigthBord, singleRow());

    m_numberTitle = QRect(m_leftBord, m_title.bottom() + point(5), point(10), singleRow() * 4);
    m_number_I = QRect(m_numberTitle.left(), m_numberTitle.bottom(), m_numberTitle.width(), singleRow() * 2);
    m_number_II = QRect(m_numberTitle.left(), m_number_I.bottom(), m_numberTitle.width(), m_number_I.height());
    m_number_III = QRect(m_numberTitle.left(), m_number_II.bottom(), m_numberTitle.width(), m_number_I.height());
    m_number_IV = QRect(m_numberTitle.left(), m_number_III.bottom(), m_numberTitle.width(), m_number_I.height());
    m_number_V = QRect(m_numberTitle.left(), m_number_IV.bottom(), m_numberTitle.width(), m_number_I.height());

    m_workTitle = QRect(m_numberTitle.right(), m_numberTitle.top(), point(70), m_numberTitle.height());
    m_workStudy = QRect(m_workTitle.left(), m_workTitle.bottom(), m_workTitle.width(), m_number_I.height());
    m_workMethod = QRect(m_workTitle.left(), m_workStudy.bottom(), m_workTitle.width(), m_workStudy.height());
    m_workResearch = QRect(m_workTitle.left(), m_workMethod.bottom(), m_workTitle.width(), m_workStudy.height());
    m_workSport = QRect(m_workTitle.left(), m_workResearch.bottom(), m_workTitle.width(), m_workStudy.height());
    m_workOther = QRect(m_workTitle.left(), m_workSport.bottom(), m_workTitle.width(), m_workStudy.height());
    m_workTotal = QRect(m_numberTitle.left(), m_workOther.bottom(), m_numberTitle.width() + m_workTitle.width() -1, m_workStudy.height());

    m_semestrTitle = QRect(m_workTitle.right(), m_numberTitle.top(), point(117), m_numberTitle.height() / 2);
    m_semestrTitle_I = QRect(m_semestrTitle.left(), m_semestrTitle.bottom(), m_semestrTitle.width() / 3, m_numberTitle.height() / 2 + 1);
    m_semestrTitle_II = QRect(m_semestrTitle_I.right(), m_semestrTitle.bottom(), m_semestrTitle_I.width() + 1, m_semestrTitle_I.height());
    m_yearTitle = QRect(m_semestrTitle_II.right(), m_semestrTitle.bottom(), m_semestrTitle_I.width() + 1, m_semestrTitle_I.height());

    m_workStudy_I = QRect(m_semestrTitle_I.left(), m_semestrTitle_I.bottom(), m_semestrTitle_I.width(), m_number_I.height());
    m_workMethod_I = QRect(m_semestrTitle_I.left(), m_workStudy_I.bottom(), m_semestrTitle_I.width(), m_number_II.height());
    m_workResearch_I = QRect(m_semestrTitle_I.left(), m_workMethod_I.bottom(), m_semestrTitle_I.width(), m_number_III.height());
    m_workSport_I = QRect(m_semestrTitle_I.left(), m_workResearch_I.bottom(), m_semestrTitle_I.width(), m_number_IV.height());
    m_workOther_I = QRect(m_semestrTitle_I.left(), m_workSport_I.bottom(), m_semestrTitle_I.width(), m_number_V.height());
    m_workTotal_I = QRect(m_semestrTitle_I.left(), m_workOther_I.bottom(), m_semestrTitle_I.width(), m_workTotal.height());

    m_workStudy_II = QRect(m_semestrTitle_II.left(), m_semestrTitle_II.bottom(), m_semestrTitle_II.width(), m_number_I.height());
    m_workMethod_II = QRect(m_semestrTitle_II.left(), m_workStudy_II.bottom(), m_semestrTitle_II.width(), m_number_II.height());
    m_workResearch_II = QRect(m_semestrTitle_II.left(), m_workMethod_II.bottom(), m_semestrTitle_II.width(), m_number_III.height());
    m_workSport_II = QRect(m_semestrTitle_II.left(), m_workResearch_II.bottom(), m_semestrTitle_II.width(), m_number_IV.height());
    m_workOther_II = QRect(m_semestrTitle_II.left(), m_workSport_II.bottom(), m_semestrTitle_II.width(), m_number_V.height());
    m_workTotal_II = QRect(m_semestrTitle_II.left(), m_workOther_II.bottom(), m_semestrTitle_II.width(), m_workTotal.height());

    m_workStudy_year = QRect(m_yearTitle.left(), m_yearTitle.bottom(), m_yearTitle.width(), m_number_I.height());
    m_workMethod_year = QRect(m_yearTitle.left(), m_workStudy_year.bottom(), m_yearTitle.width(), m_number_II.height());
    m_workResearch_year = QRect(m_yearTitle.left(), m_workMethod_year.bottom(), m_yearTitle.width(), m_number_III.height());
    m_workSport_year = QRect(m_yearTitle.left(), m_workResearch_year.bottom(), m_yearTitle.width(), m_number_IV.height());
    m_workOther_year = QRect(m_yearTitle.left(), m_workSport_year.bottom(), m_yearTitle.width(), m_number_V.height());
    m_workTotal_year = QRect(m_yearTitle.left(), m_workOther_year.bottom(), m_yearTitle.width(), m_workTotal.height());

    m_protocolTitle = QRect(m_leftBord, m_workTotal.bottom() + point(20), m_rigthBord, singleRow());
    m_protocolNumber = QRect(m_leftBord, m_protocolTitle.bottom() + point(3), m_rigthBord, singleRow());
}
