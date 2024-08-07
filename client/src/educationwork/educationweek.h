#ifndef EDUCATIONWEEK_H
#define EDUCATIONWEEK_H

#include "educationalhour.h"

#include <QWidget>

namespace Ui {
class EducationWeek;
}

class EducationWeek : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWeek(int number, bool readOnly = false, QWidget *parent = nullptr);
    ~EducationWeek();

    int number() const;
    int getTime(EducationalHour::HourType type);
    void setTime(EducationalHour::HourType type, int value);

signals:
    void hoursChanged(EducationalHour::HourType, int, int);

private slots:
    void on_line_plan_textEdited(const QString &arg1);
    void on_line_fact_textEdited(const QString &arg1);

private:
    Ui::EducationWeek *ui;
    const int m_number;
};

#endif // EDUCATIONWEEK_H
