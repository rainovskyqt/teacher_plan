#ifndef EDUCATIONWEEK_H
#define EDUCATIONWEEK_H

#include "educationalhour.h"

#include <QWidget>

#include <database/models/teacherwork.h>

namespace Ui {
class EducationWeek;
}

class EducationWeek : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWeek(EducationalHour *planHour, EducationalHour *factHour,
                           bool planReadOnly = false, bool factReadOnly = false, QWidget *parent = nullptr);
    ~EducationWeek();

    int number() const;
    int getTime(EducationalHour::HourType type);
    void setTime(EducationalHour *hour);
    void clear();
    void setNewWorkId(int id);

signals:
    void hoursChanged(EducationalHour *hour);

private slots:
    void on_line_plan_textEdited(const QString &arg1);
    void on_line_fact_textEdited(const QString &arg1);

private:
    Ui::EducationWeek *ui;

    const int m_number;
    EducationalHour *m_planHour;
    EducationalHour *m_factHour;
};

#endif // EDUCATIONWEEK_H
