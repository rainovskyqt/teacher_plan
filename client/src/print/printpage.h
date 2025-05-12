#ifndef PRINTPAGE_H
#define PRINTPAGE_H

#include "datafiles/printdata.h"

#include <QWidget>

class QPrinter;

namespace Ui {
class PrintPage;
}

class PrintPage : public QWidget
{
    Q_OBJECT

public:
    enum class PagePosition{
        First,
        Middle,
        Last
    };

    explicit PrintPage(int absWigth, int absHeight, int coefficient, PagePosition position, QWidget *parent = nullptr);
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
    const int m_leftBord;
    const int m_rigthBord;
    const int m_topBord;
    const int m_bottomBord;
    const PagePosition m_pagePosition;

    PrintData m_data;

    QFont m_fontMain;
    QFont m_fontMainBold;
    QFont m_fontTitle;

    virtual void paintData(QPainter &painter) = 0;
    virtual void setRects() = 0;

    int point(int absPoint);
    void drawCell(QPainter *p, QRect r, int flag = 0, QString text = "", double modification = 1.0, bool vertical = false);
    double singleRow();
};

#endif // PRINTPAGE_H
