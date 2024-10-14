#ifndef MONTHHEADER_H
#define MONTHHEADER_H

#include <QWidget>

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
};

#endif // MONTHHEADER_H
