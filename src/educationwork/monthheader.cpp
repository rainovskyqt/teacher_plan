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

    // ui->lbl_name->setText(Months::get()->name(month));
    // m_firstSemester = Months::get()->isFirstSemester(month);
    // setWeeks(month);
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

// bool MonthHeader::isFirstSemester() const
// {
    // return m_firstSemester;
// }

void MonthHeader::setWeeks(Months::Month month)
{

}

// void MonthHeader::setWeeks(Months::Month month)
// {
    // QPair<int, int> weeks = Months::get()->monthWeeks(month);
    // int start = weeks.first;
    // int count = weeks.second;

    // ui->lbl_week_1->setNum(start);
    // ui->lbl_week_2->setNum(start + 1);
    // ui->lbl_week_3->setNum(start + 2);
    // ui->lbl_week_4->setNum(start + 3);
    // if(count >= 5){
    //     ui->lbl_week_5->setNum(start + 4);
    // } else {
    //     ui->w_5->setVisible(false);
    // }
// }
