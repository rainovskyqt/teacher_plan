#include "pageanalysis.h"

#include <QPainter>

#define ROW_COUNT 10
#define ROW_COF 1.2

PageAnalysis::PageAnalysis(int wigth, int height, int coefficient, PagePosition position, QWidget *parent) :
    PrintPage(wigth, height, coefficient, position, parent)
{
}

void PageAnalysis::setData(PrintData* data)
{
    m_data = qobject_cast<PrintAnalysisData*>(data);
}

void PageAnalysis::paintData(QPainter &painter)
{
    painter.setFont(m_fontMain);

    painter.drawText(m_title, Qt::AlignCenter, "VI. АНАЛИЗ ВЫПОЛНЕНИЯ ИНДИВИДУАЛЬНОГО ПЛАНА");
    painter.drawText(m_half, Qt::AlignCenter, QString("%1-е полугодие\n"
                                                       "Пояснения преподавателя по результатам выполнения нагрузки %2:")
                                                  .arg(m_data->isSecond() ? "2" : "1",
                                                       m_data->isSecond() ? "2-го полугодия и за год в целом" : "1-го полугодия"));
    int row = m_half.bottom();
    for(int rowNumber = 1; rowNumber <= ROW_COUNT; ++rowNumber){
        int line = row + (singleRow() * ROW_COF) * rowNumber;
        painter.drawLine(m_leftBord, line, m_rigthBord, line);
    }

    painter.drawText(m_teacherSign, Qt::AlignLeft, QString("Преподаватель ______________________/%1\n\n"
                                                           "\"______\"____________________ 20____г.")
                                                       .arg("________________"));

    painter.drawText(m_cheefTitle, Qt::AlignCenter, QString("Заключение заведующего кафедрой о выполнении нагрузки и качестве работы\n"
                                                            " преподавателя в %1:")
                                                        .arg(m_data->isSecond() ? "2-ом полугодии и за год в целом" :  "1-ом полугодии"));

    row = m_cheefTitle.bottom();
    for(int rowNumber = 1; rowNumber <= ROW_COUNT; ++rowNumber){
        int line = row + (singleRow() * ROW_COF) * rowNumber;
        painter.drawLine(m_leftBord, line, m_rigthBord, line);
    }

    painter.drawText(m_cheefSign, Qt::AlignLeft, QString("Зав. кафедрой ______________________/%1\n\n"
                                                           "\"______\"____________________ 20____г.")
                                                       .arg("______________________."));

    painter.drawText(m_protocol, Qt::AlignLeft, QString("Выполнение Индивидуального плана рассмотрено на заседании кафедры,\n"
                                                           "протокол № ______ от \"______\"____________________ 20____г."));
}


void PageAnalysis::setRects()
{
    m_title = QRect(m_leftBord, point(5), m_rigthBord, singleRow());
    m_half = QRect(m_leftBord, m_title.bottom(), m_rigthBord, singleRow() * 2);
    m_teacherSign = QRect(m_leftBord, m_half.bottom() + (singleRow() * ROW_COF) * ROW_COUNT + point(7), m_rigthBord, singleRow() * 2.5);
    m_cheefTitle = QRect(m_leftBord, m_teacherSign.bottom() + point(3), m_rigthBord, singleRow() * 2);
    m_cheefSign = QRect(m_leftBord, m_cheefTitle.bottom() + (singleRow() * ROW_COF) * ROW_COUNT + point(5), m_rigthBord, singleRow() * 2.5);
    m_protocol = QRect(m_leftBord, m_cheefSign.bottom() + point(3), m_rigthBord, singleRow() * 2);
}
