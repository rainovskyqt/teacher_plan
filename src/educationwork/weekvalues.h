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

    void setPlaneReadOnly(bool readOnly);
    void setFactReadOnly(bool readOnly);

signals:
    void valueUpdated(int);

private slots:


private:
    Ui::WeekValues *ui;
    int m_week;
    Hour *m_hours;
};

#endif // WEEKVALUES_H
