#ifndef FORMEDUCATIONWORK_H
#define FORMEDUCATIONWORK_H

#include <QWidget>

#include <database/models/teacherplan.h>

namespace Ui {
class FormEducationWork;
}

class FormEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit FormEducationWork(QWidget *parent = nullptr);
    ~FormEducationWork();

public slots:
    void setPlanData(TeacherPlan *plan);

private:
    Ui::FormEducationWork *ui;

    void setTable();
};

#endif // FORMEDUCATIONWORK_H
