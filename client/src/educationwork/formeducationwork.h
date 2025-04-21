#ifndef FORMEDUCATIONWORK_H
#define FORMEDUCATIONWORK_H

#include "educationalhour.h"

#include <QWidget>

#include <database/models/teacherplan.h>
#include <database/models/datamodels.h>

#include <misc/month.h>

class PrintStudyData;

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
    void setStudyTime(PrintStudyData *c);

private slots:
    void on_btn_add_clicked();
    void deleteRow();
    void countFactValue(Month::Months month, int workType, int, EducationalHour::HourType hourType);

signals:
    void planValueChanged(WorkType, PlanTime::Semester, int);
    void factValueChanged(Month::Months, int, int);
    void monthValueChanged(Month::Months, int, int, EducationalHour::HourType);

    void clear();

private:
    Ui::FormEducationWork *ui;

    TeacherPlan *m_plan;

    void clearData();
    void setTable();
    void fillTable();
    void addRow(EducationalWork *work);
    int countHours(EducationalHour::HourType type, int week);
    void updateRowNumber(int start);
};

#endif // FORMEDUCATIONWORK_H
