#ifndef FORMTOTALTIME_H
#define FORMTOTALTIME_H

#include <QLineEdit>

#include <QWidget>
#include <QSpinBox>
#include <QButtonGroup>
#include <QLabel>

#include "educationwork/hours.h"
#include "database/types.h"

namespace Ui {
class FormTotalTime;
}

class FormTotalTime : public QWidget
{
    Q_OBJECT

public:
    explicit FormTotalTime(QWidget *parent = nullptr);
    ~FormTotalTime();

public slots:
    void updateValues(const WorkType type, const TotalHour *vals);
    void setRate(double rate);

signals:
    void rateChanged(double rate);

private slots:
    void changeRate(bool toggled);


private:
    Ui::FormTotalTime *ui;

    PlanTotalHour m_totalHours;

    void colorHours();
    void colorHour(QLabel *lbl, QSpinBox *sBox);
    void createConnections();
    void setValues();
    void setValue(QSpinBox *first, QSpinBox *second, QSpinBox *total, const TotalHour *vals);
    void setRateBtn(double rate);
    void setTotal();
};

#endif // FORMTOTALTIME_H
