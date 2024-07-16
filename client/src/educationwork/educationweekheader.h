#ifndef EDUCATIONWEEKHEADER_H
#define EDUCATIONWEEKHEADER_H

#include <QWidget>

namespace Ui {
class EducationWeekHeader;
}

class EducationWeekHeader : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWeekHeader(int number, QWidget *parent = nullptr);
    ~EducationWeekHeader();

    int startDay();
    void setStartDay(int start);
    int endDay();
    void setEndDay(int end);
    int weekNumber();

private:
    Ui::EducationWeekHeader *ui;
};

#endif // EDUCATIONWEEKHEADER_H
