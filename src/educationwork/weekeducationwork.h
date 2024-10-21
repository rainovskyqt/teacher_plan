#ifndef WEEKEDUCATIONWORK_H
#define WEEKEDUCATIONWORK_H

#include <QLineEdit>
#include <QWidget>

#include "modeleducationwork.h"

using HT = ModelEducationWork::HourType;
using H = ModelEducationWork::Hour;


namespace Ui {
class WeekEducationWork;
}

class WeekEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit WeekEducationWork(const QHash<int, H> &hours, QWidget *parent = nullptr);
    ~WeekEducationWork();

signals:
    void valueChanged(int, HT, int);           //id, тип, значение

private slots:
    void updateValue(QString text);

private:
    Ui::WeekEducationWork *ui;
    void initFieds(const QHash<int, H> &hours);
    void setClearingField(QLineEdit *editor);
    void setWeekProperty(QLineEdit *editor);
    void setValues(QList<QLineEdit *> editors, const QHash<int, H> &hours);
};

#endif // WEEKEDUCATIONWORK_H
