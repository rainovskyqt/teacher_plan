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
    explicit WeekEducationWork(QWidget *parent = nullptr);
    ~WeekEducationWork();
    void setValues(const QHash<int, H> &hours);
    QPair<int, int> totalValue(HT type);

signals:
    void valueChanged(int, HT, int, int);           //id, тип, значение, неделя

private slots:
    void updateValue(QString text);

private:
    Ui::WeekEducationWork *ui;

    QList<QLineEdit *> m_planeFields;
    QList<QLineEdit *> m_factFields;

    void initFieds();
    void setFieldType(QLineEdit *editor);
    void setClearingField(QLineEdit *editor);
    void setWeekProperty(QLineEdit *editor);
};

#endif // WEEKEDUCATIONWORK_H
