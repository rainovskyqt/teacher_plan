#ifndef EDUCATIONMONTH_H
#define EDUCATIONMONTH_H

#include <QMap>
#include <QWidget>

#include "misc/month.h"
#include "educationalhour.h"

namespace Ui {
class EducationMonth;
}

class EducationMonth : public QWidget
{
    Q_OBJECT

public:
    explicit EducationMonth(Month::Months month, int start, int count, int workId, bool planReadOnly = false,
                            bool factReadOnly = false, QWidget *parent = nullptr);
    ~EducationMonth();

    int getTime(EducationalHour::HourType type, int week = 0);

    bool isFirstSemester() const;
    void setValue(EducationalHour *hour);
    bool haveCurrentWeek(int week);
    void clear();
    void setNewWorkId(int id);

    Month::Months month() const;

signals:
    void hoursChanged(EducationalHour *hour);

private:
    Ui::EducationMonth *ui;
    bool m_isFirstSemester;
    Month::Months m_month;
    int m_startWeek;
    int m_endWeek;

    void addWeeks(int start, int count, int workId, bool planReadOnly, bool factReadOnly);
};

#endif // EDUCATIONMONTH_H
