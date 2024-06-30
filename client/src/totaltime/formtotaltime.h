#ifndef FORMTOTALTIME_H
#define FORMTOTALTIME_H

#include <QLineEdit>

#include <QWidget>
#include<QSpinBox>
#include <QButtonGroup>

#include <database/models/teacherplan.h>

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

public slots:
    void setPlanData(TeacherPlan *plan);

signals:
//    void modelDataChanged();
//    void savePlan();
    void rateChanged(double);

private:
    Ui::FormTotalTime *ui;

//    ModelTotalTime m_model;

//    QVector<QSpinBox*> m_totals;
//    QVector<QSpinBox*> m_years;
//    QVector<QSpinBox*> m_current;
    QButtonGroup *m_rateGroup;

    void setRate(double rate);
//    void setTable();
    void createConnections();
//    int getCount();

};

#endif // FORMTOTALTIME_H
