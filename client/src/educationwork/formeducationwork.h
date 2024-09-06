#ifndef FORMEDUCATIONWORK_H
#define FORMEDUCATIONWORK_H

#include "educationalhour.h"

#include <QWidget>

#include <database/models/teacherplan.h>

#include <misc/month.h>

namespace Ui {
class FormEducationWork;
}

class EducationalWork;

class FormEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit FormEducationWork(QWidget *parent = nullptr);
    ~FormEducationWork();

public slots:
    void setPlanData(TeacherPlan *plan);

private slots:
    void on_btn_add_clicked();
    void deleteRow();

signals:
    void firstPlaneChanged(int);
    void secondPlaneChanged(int);
    void factValueChanged(Month::Months, int, int);

    void clear();

private:
    Ui::FormEducationWork *ui;

    TeacherPlan *m_plan;

    void clearData();
    void setTable();
    void fillTable();
    void addRow(EducationalWork *work);
    int countHours(EducationalHour::HourType type, int week);
};

#endif // FORMEDUCATIONWORK_H
