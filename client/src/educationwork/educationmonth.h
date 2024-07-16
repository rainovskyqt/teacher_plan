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
    explicit EducationMonth(int start, int count, bool readOnly = false, QWidget *parent = nullptr);
    ~EducationMonth();

    int getTime(EducationalHour::HourType type, int week = 0);

    bool isFirstSemester() const;
    void setValue(EducationalHour::HourType type, int week, int value);
    bool haveCurrentWeek(int week);

signals:
    void hoursChanged(EducationalHour::HourType, int, int);

private:
    Ui::EducationMonth *ui;
    void addWeeks(int start, int count, bool readOnly);
    bool m_isFirstSemester;
    int m_startWeek;
    int m_endWeek;
};

#endif // EDUCATIONMONTH_H
