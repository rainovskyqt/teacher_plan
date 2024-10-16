#include "monthheader.h"
#include "ui_monthheader.h"

MonthHeader::MonthHeader(Months::Month month, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MonthHeader)
{
    ui->setupUi(this);
    ui->lbl_name->setText(Months::get()->name(month));
    m_firstSemester = Months::get()->isFirstSemester(month);
    setWeeks(month);
}

MonthHeader::~MonthHeader()
{
    delete ui;
}

bool MonthHeader::isFirstSemester() const
{
    return m_firstSemester;
}

void MonthHeader::setWeeks(Months::Month month)
{
    QPair<int, int> weeks = Months::get()->monthWeeks(month);
    int start = weeks.first;
    int count = weeks.second;

    ui->lbl_week_1->setNum(start);
    ui->lbl_week_2->setNum(start + 1);
    ui->lbl_week_3->setNum(start + 2);
    ui->lbl_week_4->setNum(start + 3);
    if(count >= 5){
        ui->lbl_week_5->setNum(start + 4);
    } else {
        ui->w_5->setVisible(false);
    }
}
