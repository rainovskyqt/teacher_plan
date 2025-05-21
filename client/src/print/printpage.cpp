#include "printpage.h"
#include "ui_printpage.h"

#include <QPainter>
#include <QPrinter>

PrintPage::PrintPage(int absWigth, int absHeight, int coefficient, PagePosition position, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrintPage)
    , m_coef(coefficient)
    , m_wigth(point(absWigth))
    , m_height(point(absHeight))
    , m_leftBord(point(10))
    , m_rigthBord(m_wigth - m_leftBord - point(10))
    , m_topBord(point(10))
    , m_bottomBord(m_height - point(10))
    , m_pagePosition(position)
{
    ui->setupUi(this);
}

PrintPage::~PrintPage()
{
    delete ui;
}

void PrintPage::print(QPrinter *printer)
{
    QPainter p;

    int phys_w = printer->width();
    int phys_h = printer->height();

    p.begin(printer);
    p.setWindow(0,0, m_wigth, m_height);
    p.setViewport(0, 0, phys_w, phys_h);
    paintData(p);
    p.end();
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
    setFonts();
    setRects();
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

void PrintPage::drawCell(QPainter *p, QRect r, int flag, QString text, double modification, bool vertical)
{
    p->save();

    p->setFont(QFont(p->font().family(), p->font().pointSize() * modification));

    p->drawRect(r);

    if(vertical){
        p->translate(r.x(), r.y());
        p->rotate(-90);
        p->drawText(-r.height(), 0, r.height(), r.width(), flag, text);
    } else {
        p->drawText(r, flag, text);
    }
    p->restore();
}

double PrintPage::singleRow()
{
    int size = m_fontTitle.pointSize() * 1.7;
    if(size % 2)
        size++;
    return size;
}
