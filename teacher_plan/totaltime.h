#ifndef TOTALTIME_H
#define TOTALTIME_H

#include <QWidget>

namespace Ui {
class TotalTime;
}

class TotalTime : public QWidget
{
    Q_OBJECT

public:
    explicit TotalTime(QWidget *parent = nullptr);
    ~TotalTime();

private:
    Ui::TotalTime *ui;
};

#endif // TOTALTIME_H
