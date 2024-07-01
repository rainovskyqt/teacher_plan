#ifndef FORMEDUCATIONWORK_H
#define FORMEDUCATIONWORK_H

#include <QWidget>

#include <database/models/teacherplan.h>

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

private:
    Ui::FormEducationWork *ui;

    TeacherPlan *m_plan;

    void setTable();
    void fillTable();
    void addRow(EducationalWork *work);
};

#endif // FORMEDUCATIONWORK_H
