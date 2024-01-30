#ifndef TOTALTIME_H
#define TOTALTIME_H

#include "totaltimelist.h"
#include <QLineEdit>

#include <QWidget>
#include<QSpinBox>

namespace Ui {
class TotalTime;
}

class TotalTime : public QWidget
{
    Q_OBJECT

public:
    explicit TotalTime(QWidget *parent = nullptr);
    ~TotalTime();

private slots:
    void on_btn_save_clicked();


private:
    Ui::TotalTime *ui;

    TotalTimeList *m_totalTimeList;
    QVector<QSpinBox*> m_totals;
    QVector<QSpinBox*> m_years;
    QVector<QSpinBox*> m_current;

    void createConnections();
    void loadHours();
    void setHoursInForm(TotalTimeList *totalTime);
    int getCount();
};

#endif // TOTALTIME_H
