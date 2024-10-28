#ifndef WEEKEDUCATIONWORK_H
#define WEEKEDUCATIONWORK_H

#include <QWidget>

#include "modeleducationwork.h"
#include "weekvalues.h"
#include "educationwork.h"

using HT = ModelEducationWork::HourType;
using H = Hour;


namespace Ui {
class WeekEducationWork;
}

class WeekEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit WeekEducationWork(bool planeReadOnly, bool factReadOnly, QWidget *parent = nullptr);
    ~WeekEducationWork();
    void setValues(const QMap<int, Hour*> &hours);

signals:
    void valueChanged(int);

private:
    Ui::WeekEducationWork *ui;

    void initFieds(bool planeReadOnly, bool factReadOnly);
    void setWeekProperty(WeekValues *editor);
};

#endif // WEEKEDUCATIONWORK_H
