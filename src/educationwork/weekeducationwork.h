#ifndef WEEKEDUCATIONWORK_H
#define WEEKEDUCATIONWORK_H

#include <QLineEdit>
#include <QWidget>

#include "modeleducationwork.h"

namespace Ui {
class WeekEducationWork;
}

class WeekEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit WeekEducationWork(ModelEducationWork::Hour hour, QWidget *parent = nullptr);
    ~WeekEducationWork();

signals:
    void valueChanged(int, int, int);           //id, plane, fact

private slots:
    void clearField(QString text);

private:
    Ui::WeekEducationWork *ui;

    int m_id;

    void setClearingField(QLineEdit *editor);
};

#endif // WEEKEDUCATIONWORK_H
