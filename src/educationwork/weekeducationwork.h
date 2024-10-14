#ifndef WEEKEDUCATIONWORK_H
#define WEEKEDUCATIONWORK_H

#include <QWidget>

namespace Ui {
class WeekEducationWork;
}

class WeekEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit WeekEducationWork(QWidget *parent = nullptr);
    ~WeekEducationWork();

private:
    Ui::WeekEducationWork *ui;
};

#endif // WEEKEDUCATIONWORK_H
