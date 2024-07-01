#ifndef FORMTOTALTIME_H
#define FORMTOTALTIME_H

#include <QLineEdit>

#include <QWidget>
#include<QSpinBox>
#include <QButtonGroup>
#include <QLabel>

#include <database/models/teacherplan.h>

#include "misc/HierarchicalHeaderView.h"

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
    void setPlanData(TeacherPlan *plan);

signals:
//    void modelDataChanged();
//    void savePlan();
    void rateChanged(double);

private slots:
    void on_sb_eduYear_valueChanged(int arg1);
    void on_sb_totalYear_valueChanged(int arg1);
    void countYearTime();

private:
    Ui::FormTotalTime *ui;

//    ModelTotalTime m_model;

//    QVector<QSpinBox*> m_totals;
//    QVector<QSpinBox*> m_years;
//    QVector<QSpinBox*> m_current;
    QButtonGroup *m_rateGroup;
    QMap<QPair<QSpinBox*,QSpinBox*>, QSpinBox*> m_hours;

    void setRate(double rate);
    void createConnections();
    void colorHours(QLabel *lbl, QSpinBox *sBox);
    void makeTimeConnections();
    void countFirstSemester();
    void countSecondSemester();

//    int getCount();

};

#endif // FORMTOTALTIME_H
