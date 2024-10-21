#include "monthheader.h"
#include "ui_monthheader.h"

#include <QRegularExpression>

#define FOUR_WEEK 160
#define FIVE_WEEK 200

MonthHeader::MonthHeader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonthHeader)
{
    ui->setupUi(this);
    setMonthsHeaders();
    setWeeks();
}

MonthHeader::~MonthHeader()
{
    delete ui;
}

void MonthHeader::setMonthsHeaders()
{
    QRegularExpression nameMask("lbl_name_\\d+");
    auto lbls = findChildren<QLabel*>(nameMask);

    for(auto lbl : lbls){
        auto month = (Months::Month)lbl->property("monthNUmber").toInt();
        auto weeks = Months::get()->monthWeeks(month);
        int width = weeks.second > 4 ? FIVE_WEEK : FOUR_WEEK;
        lbl->setMaximumWidth(width);
        lbl->setText(Months::get()->name(month));
    }
}


void MonthHeader::setWeeks()
{
    auto weeks = Months::get()->weekDates();

    auto lbls = findChildren<QLabel*>(QRegularExpression("lbl_s_\\d+"));
    lbls.append(findChildren<QLabel*>(QRegularExpression("lbl_e_\\d+")));
    for(auto l : lbls){
        QString name = l->objectName();
        bool isStart = name.contains("_s_");
        QString strWeek = name.rightRef(2).toString();
        int weekNumber = strWeek.remove("_").toInt();

        auto week = weeks.value(weekNumber);
        l->setNum(isStart ? week.first : week.second);
    }
}
