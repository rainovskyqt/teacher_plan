#ifndef EDUCATIONMONTH_H
#define EDUCATIONMONTH_H

#include <QMap>
#include <QWidget>

#include "misc/month.h"

namespace Ui {
class EducationMonth;
}

class EducationMonth : public QWidget
{
    Q_OBJECT

public:

    explicit EducationMonth(Month::Months month, int startWeek,
                            int weekCount, QWidget *parent = nullptr);
    ~EducationMonth();

private:
    Ui::EducationMonth *ui;
    void addWeeks(int start, int count);
};

#endif // EDUCATIONMONTH_H
