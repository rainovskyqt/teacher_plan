#include "educationmonth.h"
#include "educationweek.h"
#include "ui_educationmonth.h"
#include "settings.h"

EducationMonth::EducationMonth(int start, int count, int workId, bool readOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationMonth),
    m_isFirstSemester(true)
{
    ui->setupUi(this);
    addWeeks(start, count, workId, readOnly);

    if(start >= Settings::get().secondSemesterWeek())
        m_isFirstSemester = false;
}

EducationMonth::~EducationMonth()
{
    delete ui;
}

int EducationMonth::getTime(EducationalHour::HourType type, int week)
{
    int count = 0;
    auto weeks = this->findChildren<EducationWeek*>();
    for(auto w: weeks){
        if(week && (week != w->number()))
            continue;
        count += w->getTime(type);
    }
    return count;
}

void EducationMonth::addWeeks(int start, int count, int workId, bool readOnly)
{
    m_startWeek = start;
    m_endWeek = start + count;

    for(int i = start; i < m_endWeek; ++i){
        auto week = new EducationWeek(new EducationalHour(0, workId, i, 0, EducationalHour::Plane, this),
                                      new EducationalHour(0, workId, i, 0, EducationalHour::Factical, this),
                                      readOnly, this);

        connect(week, &EducationWeek::hoursChanged, this, &EducationMonth::hoursChanged);

        ui->hl_weeks->addWidget(week);
    }
}

bool EducationMonth::isFirstSemester() const
{
    return m_isFirstSemester;
}

void EducationMonth::setValue(EducationalHour* hour)
{
    if(!haveCurrentWeek(hour->week()))
        return;

    auto weeks = this->findChildren<EducationWeek*>();
    for(auto w: weeks){
        if(w->number() == hour->week())
            w->setTime(hour);
    }
}

bool EducationMonth::haveCurrentWeek(int week)
{
    return (week >= m_startWeek && week <= m_endWeek);
}

void EducationMonth::clear()
{
    auto weeks = this->findChildren<EducationWeek*>();
    for(auto w: weeks)
        w->clear();
}
