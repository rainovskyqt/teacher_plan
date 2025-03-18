#ifndef PRINTPAGE_H
#define PRINTPAGE_H

#include "printdata.h"

#include <QWidget>

class QPrinter;

namespace Ui {
class PrintPage;
}

class PrintPage : public QWidget
{
    Q_OBJECT

public:
    explicit PrintPage(int absWigth, int absHeight, int coefficient, QWidget *parent = nullptr);
    ~PrintPage();

    virtual void print(QPrinter *printer);
    virtual void paintEvent(QPaintEvent *e);
    virtual void setData(PrintData *data) = 0;
    void init();

private:
    Ui::PrintPage *ui;
    void setFonts();

protected:
    const int m_coef;
    const int m_wigth;
    const int m_height;
    PrintData m_data;

    QFont m_fontMain;
    QFont m_fontMainBold;
    QFont m_fontTitle;

    virtual void paintData(QPainter &painter) = 0;
    virtual void setRects() = 0;

    int point(int absPoint);
};

#endif // PRINTPAGE_H
