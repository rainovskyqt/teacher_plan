#ifndef EDUCATIONWEEK_H
#define EDUCATIONWEEK_H

#include <QWidget>

namespace Ui {
class EducationWeek;
}

class EducationWeek : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWeek(int number, QWidget *parent = nullptr);
    ~EducationWeek();

    int startDay();
    void setStartDay(int start);
    int endDay();
    void setEndDay(int end);
    int weekNumber();
    void setWeekNumber(int number);

private:
    Ui::EducationWeek *ui;

};

#endif // EDUCATIONWEEK_H
