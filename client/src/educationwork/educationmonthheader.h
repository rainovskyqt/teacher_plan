#ifndef EDUCATIONMONTHHEADER_H
#define EDUCATIONMONTHHEADER_H

#include <QWidget>

#include <misc/month.h>

namespace Ui {
class EducationMonthHeader;
}

class EducationMonthHeader : public QWidget
{
    Q_OBJECT

public:
    explicit EducationMonthHeader(Month::Months month, int startWeek, int weekCount, QWidget *parent = nullptr);
    ~EducationMonthHeader();

private:
    Ui::EducationMonthHeader *ui;
    void addWeeks(int start, int count);
};

#endif // EDUCATIONMONTHHEADER_H
