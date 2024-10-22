#ifndef WEEKVALUES_H
#define WEEKVALUES_H

#include <QWidget>
#include "educationwork.h"

namespace Ui {
class WeekValues;
}

class WeekValues : public QWidget
{
    Q_OBJECT

public:
    explicit WeekValues(QWidget *parent = nullptr);
    ~WeekValues();

    void setWeekValues(Hour *hours);
    void setWeek(int newWeek);
    int week() const;

    int planeValue() const;
    int factValue() const;

signals:
    // void valueUpdated(const H);

private slots:
    void updatetValue();

private:
    Ui::WeekValues *ui;
    int m_week;
    Hour *m_hours;
};

#endif // WEEKVALUES_H
