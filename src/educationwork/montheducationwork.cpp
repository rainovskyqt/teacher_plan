#include "montheducationwork.h"
#include "ui_montheducationwork.h"
#include "weekeducationwork.h"

MonthEducationWork::MonthEducationWork(QWidget *parent, Months::Month month, const QHash<int, H> &hours)
    : QWidget(parent)
    , ui(new Ui::MonthEducationWork)
{
    ui->setupUi(this);
    addWeeks(month, hours);
}

MonthEducationWork::~MonthEducationWork()
{
    delete ui;
}

void MonthEducationWork::addWeeks(Months::Month month, const QHash<int, H> &hours)
{
    QPair<int, int> weeks = Months::get()->monthWeeks(month);
    int start = weeks.first;
    int count = weeks.second;

    for(int i = start; i < start + count; ++i){
        auto week = new WeekEducationWork(hours, this);
        // connect(week, &WeekEducationWork::valueChanged, this, &MonthEducationWork::valueChanged);
        ui->hl_weeks->addWidget(week);
    }
}
