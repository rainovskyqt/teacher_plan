#include "printpage.h"
#include "ui_printpage.h"

#include <QPainter>

PrintPage::PrintPage(int absWigth, int absHeight, int coefficient, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrintPage)
    , m_coef(coefficient)
    , m_wigth(point(absWigth))
    , m_height(point(absHeight))
    , m_leftBord(point(10))
    , m_rigthBord(m_wigth - point(10))
{
    ui->setupUi(this);
}

PrintPage::~PrintPage()
{
    delete ui;
}

void PrintPage::print(QPrinter *printer)
{

}

void PrintPage::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QPainter painter(this);
    painter.setWindow(0, 0, m_wigth, m_height);
    paintData(painter);
}

void PrintPage::init()
{
    setRects();
    setFonts();
}

void PrintPage::setFonts()
{
    m_fontMain = QFont("Times New Roman", 12);

    m_fontMainBold = m_fontMain;
    m_fontMainBold.setBold(true);

    m_fontTitle = QFont("Times New Roman", 18);
    m_fontTitle.setBold(true);
}

int PrintPage::point(int absPoint)
{
    return absPoint * m_coef;
}

void PrintPage::drawCell(QPainter *p, QRect r, int flag, QString text)
{
    p->drawRect(r);
    p->drawText(r, flag, text);
}
