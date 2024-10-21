#ifndef MONTHHEADER_H
#define MONTHHEADER_H

#include <QWidget>

#include "misc/months.h"

namespace Ui {
class MonthHeader;
}

class MonthHeader : public QWidget
{
    Q_OBJECT

public:
    explicit MonthHeader(QWidget *parent = nullptr);
    ~MonthHeader();

private:
    Ui::MonthHeader *ui;

    void setMonthsHeaders();
    void setWeeks();
};

#endif // MONTHHEADER_H
