#include "printpage.h"
#include "ui_printpage.h"

#include <QPainter>

PrintPage::PrintPage(int absWigth, int absHeight, int coefficient, QWidget *parent, int semester)
    : QWidget(parent)
    , ui(new Ui::PrintPage)
    , m_coef(coefficient)
    , m_wigth(point(absWigth))
    , m_height(point(absHeight))
    , m_leftBord(point(10))
    , m_rigthBord(m_wigth - m_leftBord - point(10))
    , m_topBord(point(10))
    , m_bottomBord(m_height - point(10))
    , m_semester(semester)
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

void PrintPage::drawCell(QPainter *p, QRect r, int flag, QString text, double modification)
{
    auto font = p->font();
    auto newFont = p->font();

    newFont.setPointSize(font.pointSize() * modification);
    p->setFont(newFont);

    p->drawRect(r);
    p->drawText(r, flag, text);

    p->setFont(font);
}

double PrintPage::singleRow()
{
    return m_fontTitle.pointSize() * 1.5;
}
