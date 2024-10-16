#ifndef MONTHEDUCATIONWORK_H
#define MONTHEDUCATIONWORK_H

#include "modeleducationwork.h"
#include <QWidget>

#include <misc/months.h>

using H = ModelEducationWork::Hour;

namespace Ui {
class MonthEducationWork;
}

class MonthEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit MonthEducationWork(QWidget *parent, Months::Month month, const QHash<int, H> &hours = {});
    ~MonthEducationWork();

signals:
    void valueChanged(int, int, int);           //id, plane, fact

private:
    Ui::MonthEducationWork *ui;

    void addWeeks(Months::Month month, const QHash<int, H> &hours);
};

#endif // MONTHEDUCATIONWORK_H
