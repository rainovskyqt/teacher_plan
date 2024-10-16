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
    explicit MonthHeader(Months::Month month, QWidget *parent = nullptr);
    ~MonthHeader();

    bool isFirstSemester() const;

private:
    Ui::MonthHeader *ui;
    bool m_firstSemester;

    void setWeeks(Months::Month month);
};

#endif // MONTHHEADER_H
