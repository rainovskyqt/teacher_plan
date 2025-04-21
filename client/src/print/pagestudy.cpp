#include "pagestudy.h"

#include <QPainter>

#include "datafiles/printstudydata.h"
#include "settings.h"

PageStudy::PageStudy(int wigth, int height, int coefficient, QWidget *parent) :
    PrintPage(wigth, height, coefficient, parent)
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
    drawCell(&painter, m_month1, Qt::AlignCenter, m_data->isSecond() ? "Февраль" : "Сентябрь");
    drawCell(&painter, m_month2, Qt::AlignCenter, m_data->isSecond() ? "Март" : "Октябрь");
    drawCell(&painter, m_month3, Qt::AlignCenter, m_data->isSecond() ? "Апрель" : "Ноябрь");
    drawCell(&painter, m_month4, Qt::AlignCenter, m_data->isSecond() ? "Май" : "Декабрь");
    drawCell(&painter, m_month5, Qt::AlignCenter, m_data->isSecond() ? "Июнь" : "Январь");
    drawCell(&painter, m_totalTitle, Qt::AlignCenter, m_data->isSecond() ? "II\nсем." : "I\nсем.", 0.8);
    drawCell(&painter, m_totalYearTitle, Qt::AlignCenter, "За\nгод", 0.8);
    drawCell(&painter, m_commentsTitle, Qt::AlignCenter, "Примечание");
    drawCell(&painter, m_hoursTotalPlaneTitle, Qt::AlignCenter, "План");
    drawCell(&painter, m_hoursTotalFactTitle, Qt::AlignCenter, "Факт");

    drawCell(&painter, m_positionTitle, Qt::AlignCenter, "№\n п/п", 0.8);
    drawCell(&painter, m_workNameTitle, Qt::AlignCenter|Qt::TextWordWrap, "Наименование дисциплины, курс, группа. Виды работ", 0.8);
    drawCell(&painter, m_hoursTypeTitle, Qt::AlignCenter, "");

    int startWeek = m_data->isSecond() ? Settings::get().secondSemesterWeek() + 1 : 1;
    int endWeek = m_data->isSecond() ? 44 : Settings::get().secondSemesterWeek();

    for(int week = startWeek; week <= endWeek; ++week)
        drawWeek(painter, m_weekStartTitle, week);

    auto works = m_data->works();
    QRect position = m_positionTitle;
    position.setHeight(singleRow());
    position.moveTop(position.bottom() + 1);

    QRect name = m_workNameTitle;
    name.setHeight(singleRow());
    name.moveTop(position.top());

    QRect typePlane = m_hoursTypeTitle;
    typePlane.setHeight((singleRow() / 2) + 1);
    typePlane.moveTop(position.top());
    QRect typeFact = typePlane;
    typeFact.setHeight(typeFact.height() - 1);
    typeFact.moveTop(typePlane.bottom());

    for(auto work = works.begin(); work != works.end(); ++work){
        position.moveTop(position.bottom() + 1);
        name.moveTop(position.top());
        typePlane.moveTop(position.top());
        typeFact.moveTop(typePlane.bottom() + 1);

        drawCell(&painter, position, Qt::AlignCenter, QString::number(work.key()));
        drawCell(&painter, name, Qt::AlignJustify|Qt::TextWordWrap, work.value()->name(), 0.5);
        drawCell(&painter, typePlane, Qt::AlignCenter, "план", 0.5);
        drawCell(&painter, typeFact, Qt::AlignCenter, "факт", 0.5);
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
    m_hoursTotalFactTitle = QRect(m_totalTitle.left(), m_hoursTotalPlaneTitle.bottom() + 1, point(17), ((singleRow() * 2) / 3));

    m_positionTitle = QRect(m_workTitle.left(), m_workTitle.bottom() + 1, point(5), singleRow() * 2);
    m_workNameTitle = QRect(m_positionTitle.right() + 1, m_workTitle.bottom() + 1, point(85), singleRow() * 2);
    m_hoursTypeTitle = QRect(m_workNameTitle.right() + 1, m_workTitle.bottom() + 1, point(10), singleRow() * 2);

    m_weekStartTitle = QRect(m_hoursTypeTitle.right() + 1, m_workTitle.bottom() + 1, point(5), (singleRow() * 2) / 3);
}

