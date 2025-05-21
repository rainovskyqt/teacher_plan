#include "pagestudy.h"

#include <QPainter>

#include "datafiles/printstudydata.h"
#include "settings.h"

PageStudy::PageStudy(int wigth, int height, int coefficient, PagePosition position, QWidget *parent) :
    PrintPage(wigth, height, coefficient, position, parent)
    , m_data(nullptr)
{
}

void PageStudy::setData(PrintData *data)
{
    m_data = qobject_cast<PrintStudyData*>(data);
    setRects();
}

void PageStudy::paintData(QPainter &painter)
{
    painter.setFont(m_fontMainBold);

    drawCell(&painter, m_workTitle, Qt::AlignLeft, "I. УЧЕБНАЯ РАБОТА");
    drawCell(&painter, m_month1, Qt::AlignCenter, m_data->isSecond() ? "Февраль" : "Сентябрь", 0.8);
    drawCell(&painter, m_month2, Qt::AlignCenter, m_data->isSecond() ? "Март" : "Октябрь", 0.8);
    drawCell(&painter, m_month3, Qt::AlignCenter, m_data->isSecond() ? "Апрель" : "Ноябрь", 0.8);
    drawCell(&painter, m_month4, Qt::AlignCenter, m_data->isSecond() ? "Май" : "Декабрь", 0.8);
    drawCell(&painter, m_month5, Qt::AlignCenter, m_data->isSecond() ? "Июнь" : "Январь", 0.8);
    drawCell(&painter, m_totalTitle, Qt::AlignCenter, m_data->isSecond() ? "II\nсем." : "I\nсем.", 0.8);
    if(m_data->isSecond())
        drawCell(&painter, m_totalYearTitle, Qt::AlignCenter, "За\nгод", 0.8);
    drawCell(&painter, m_commentsTitle, Qt::AlignCenter, "Примечание");
    drawCell(&painter, m_hoursTotalPlaneTitle, Qt::AlignCenter, "План", 0.8);
    drawCell(&painter, m_hoursTotalFactTitle, Qt::AlignCenter, "Факт", 0.8);

    drawCell(&painter, m_positionTitle, Qt::AlignCenter, "№\n п/п", 0.8);
    drawCell(&painter, m_workNameTitle, Qt::AlignCenter|Qt::TextWordWrap, "Наименование дисциплины, курс, группа. Виды работ", 0.8);
    drawCell(&painter, m_hoursTypeTitle, Qt::AlignCenter, "");

    int startWeek = m_data->isSecond() ? Settings::get().secondSemesterWeek() + 1 : 1;
    int endWeek = m_data->isSecond() ? 44 : Settings::get().secondSemesterWeek();

    for(int week = startWeek; week <= endWeek; ++week)
        drawWeek(painter, m_weekStartTitle, week);

    auto works = m_data->works().at(m_pagePosition == PagePosition::First ? 0 : 1);
    QRect position = m_positionTitle;
    position.setHeight(singleRow());
    position.moveTop(position.bottom() + 2);

    QRect name = m_workNameTitle;
    name.setHeight(singleRow());

    QRect type = m_hoursTypeTitle;
    type.setHeight((singleRow() / 2));

    QRect comments = m_commentsTitle;
    comments.setHeight(singleRow());

    QRect typeHours = m_totalTitle;
    typeHours.setHeight((singleRow() / 2));

    QRect typeHoursYear = m_totalYearTitle;
    typeHoursYear.setHeight((singleRow() / 2));

    for(auto work = works.begin(); work != works.end(); ++work){
        position.moveTop(position.bottom() + 2);
        name.moveTop(position.top());
        type.moveTop(position.top());
        comments.moveTop(position.top());
        typeHours.moveTop(position.top());
        typeHoursYear.moveTop(position.top());

        drawCell(&painter, position, Qt::AlignCenter, QString::number(work.key()));
        drawCell(&painter, name, Qt::AlignCenter|Qt::TextWordWrap, work.value()->name(), 0.5);
        drawCell(&painter, type, Qt::AlignCenter, "план", 0.6);

        QRect planHour = type;
        planHour.setWidth(m_weekStartTitle.width());
        planHour.moveLeft(type.right() + 1);
        type.moveTop(type.bottom() + 1);

        drawCell(&painter, type, Qt::AlignCenter, "факт", 0.6);
        QRect factHour = type;
        factHour.setWidth(m_weekStartTitle.width());
        factHour.moveLeft(type.right() + 1);
        type.moveTop(type.bottom() + 1);

        auto workHour = work.value()->hours();
        int start = m_data->isSecond() ? 23 : 1;
        int end = m_data->isSecond() ? 45 : 23;

        for(int week = start;  week < end; ++week){
            auto weekHours = workHour.value(week);
            drawCell(&painter, planHour, Qt::AlignCenter, weekHours.first == 0 ? "" : QString::number(weekHours.first), 0.7);
            planHour.moveLeft(planHour.right() + 1);

            drawCell(&painter, factHour, Qt::AlignCenter, weekHours.second == 0 ? "" : QString::number(weekHours.second), 0.7);
            factHour.moveLeft(factHour.right() + 1);
        }

        drawCell(&painter, typeHours, Qt::AlignCenter,
                 QString("%1").arg(m_data->isSecond() ? work.value()->totalPlaneII() : work.value()->totalPlaneI()), 0.7);
        typeHours.moveTop(typeHours.bottom() + 1);
        drawCell(&painter, typeHours, Qt::AlignCenter,
                 QString("%1").arg(m_data->isSecond() ? work.value()->totalFactII() : work.value()->totalFactI()), 0.7);

        if(m_data->isSecond()){
            drawCell(&painter, typeHoursYear, Qt::AlignCenter, QString("%1").arg(work.value()->totalPlaneYear()), 0.7);
            typeHoursYear.moveTop(typeHoursYear.bottom() + 1);
            drawCell(&painter, typeHoursYear, Qt::AlignCenter, QString("%1").arg(work.value()->totalFactYear()), 0.7);
        }

        drawCell(&painter, comments, Qt::AlignJustify|Qt::TextWordWrap, work.value()->comments(), 0.5);
    }
}

void PageStudy::drawWeek(QPainter &p, QRect baseRect, int week)
{
    auto dates = Settings::get().weekDate(week);
    int offset = week > Settings::get().secondSemesterWeek() ? week - Settings::get().secondSemesterWeek() : week;
    QRect writeRect = QRect(baseRect.x() + (baseRect.width() * (offset - 1)), m_weekStartTitle.y(),
                            m_weekStartTitle.width(), m_weekStartTitle.height());
    drawCell(&p, writeRect, Qt::AlignCenter, QString::number(dates.first), 0.8);
    writeRect.moveTop(writeRect.bottom() + 1);
    drawCell(&p, writeRect, Qt::AlignCenter, QString::number(dates.second), 0.8);
    writeRect.moveTop(writeRect.bottom() + 1);
    writeRect.setHeight(writeRect.height() + 2);
    drawCell(&p, writeRect, Qt::AlignCenter, QString::number(week), 0.8);
}

void PageStudy::setRects()
{
    if(m_data == nullptr)
        return;

    int five = 25;
    int four = 20;

    m_workTitle = QRect(m_leftBord, m_topBord, point(100), singleRow());
    m_month1 = QRect(m_workTitle.right() + 1, m_workTitle.top(), point(four), singleRow());
    m_month2 = QRect(m_month1.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(four) : point(five), singleRow());
    m_month3 = QRect(m_month2.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(five) : point(four), singleRow());
    m_month4 = QRect(m_month3.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(four) : point(five), singleRow());
    m_month5 = QRect(m_month4.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(five) : point(four), singleRow());
    m_totalTitle = QRect(m_month5.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(8) : point(17), singleRow() + ((singleRow() * 2) / 3));

    m_totalYearTitle = QRect(m_totalTitle.right() + 1, m_workTitle.top(), m_data->isSecond() ? point(9) : point(0),
                             singleRow() + ((singleRow() * 2) / 3));
    m_commentsTitle = QRect(m_totalYearTitle.right() + 1, m_workTitle.top(), point(50), singleRow() * 3);

    m_hoursTotalPlaneTitle = QRect(m_totalTitle.left(), m_totalTitle.bottom() + 1, point(17), ((singleRow() * 2) / 3));
    m_hoursTotalFactTitle = QRect(m_totalTitle.left(), m_hoursTotalPlaneTitle.bottom() + 1, point(17), ((singleRow() * 2) / 3) + 2);

    m_positionTitle = QRect(m_workTitle.left(), m_workTitle.bottom() + 1, point(5), singleRow() * 2);
    m_workNameTitle = QRect(m_positionTitle.right() + 1, m_workTitle.bottom() + 1, point(85), singleRow() * 2);
    m_hoursTypeTitle = QRect(m_workNameTitle.right() + 1, m_workTitle.bottom() + 1, point(10), singleRow() * 2);

    m_weekStartTitle = QRect(m_hoursTypeTitle.right() + 1, m_workTitle.bottom() + 1, point(5), (singleRow() * 2) / 3);
}

