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
    explicit WeekEducationWork(bool planeActive, bool factActive, QWidget *parent = nullptr);
    ~WeekEducationWork();
    void setValues(const QHash<int, Hour*> &hours);
    QPair<Hour, Hour> totalValues() const;

signals:
    void valueChanged(int);

private slots:
    // void updateValue(QString text);

private:
    Ui::WeekEducationWork *ui;

//     QList<QLineEdit *> m_planeFields;
//     QList<QLineEdit *> m_factFields;

    void initFieds(bool planeReadOnly, bool factReadOnly);
    void setWeekProperty(WeekValues *editor);
};

#endif // WEEKEDUCATIONWORK_H
