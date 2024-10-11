#ifndef MONTHEDUCATIONWORK_H
#define MONTHEDUCATIONWORK_H

#include <QWidget>

namespace Ui {
class MonthEducationWork;
}

class MonthEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit MonthEducationWork(QWidget *parent = nullptr);
    ~MonthEducationWork();

private:
    Ui::MonthEducationWork *ui;
};

#endif // MONTHEDUCATIONWORK_H
