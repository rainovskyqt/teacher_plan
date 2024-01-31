#ifndef FORMTOTALTIME_H
#define FORMTOTALTIME_H

#include "totaltimelist.h"
#include <QLineEdit>

#include <QWidget>
#include<QSpinBox>

#include "misc/HierarchicalHeaderView.h"

#include "modeltotaltime.h"


namespace Ui {
class FormTotalTime;
}

class FormTotalTime : public QWidget
{
    Q_OBJECT

public:
    explicit FormTotalTime(QWidget *parent = nullptr);
    ~FormTotalTime();

private slots:
    void on_btn_save_clicked();


private:
    Ui::FormTotalTime *ui;

    ModelTotalTime m_model;

    TotalTimeList *m_totalTimeList;
    QVector<QSpinBox*> m_totals;
    QVector<QSpinBox*> m_years;
    QVector<QSpinBox*> m_current;

    double m_rate;

    void setTable();
    void createConnections();
    void createRateConnections();
    void loadHours();
    void setHoursInForm(TotalTimeList *totalTime);
    int getCount();
};

#endif // FORMTOTALTIME_H
