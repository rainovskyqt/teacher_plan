#include "printpage.h"
#include "ui_printpage.h"

#include <QPainter>
#include <QPrinter>
#include <QTextLayout>

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

void PrintPage::drawCell(QPainter *p, QRect r, Qt::Alignment alignment, QString text, double modification,
                         double interval, bool vertical, bool wordWrap)
{
    p->save();
    p->setFont(QFont(p->font().family(), p->font().pointSize() * modification));

    QRect rctPaint = r;

    if (vertical) {
        p->translate(rctPaint.x(), rctPaint.y() + rctPaint.height());
        p->rotate(-90);
        rctPaint.setWidth(r.height());
        rctPaint.setHeight(r.width());
    }


    QTextOption textOption;
    textOption.setAlignment(alignment);
    if (wordWrap)
        textOption.setWrapMode(QTextOption::WordWrap);
    else
        textOption.setWrapMode(QTextOption::NoWrap);

    QTextLayout textLayout(text, p->font());
    textLayout.beginLayout();
    textLayout.setTextOption(textOption);

    qreal cursorY = 0;
    QTextLine line;

    while ((line = textLayout.createLine()).isValid()) {
        line.setLineWidth(rctPaint.width());
        if (vertical) {
            line.setPosition(QPointF(0, cursorY));
            cursorY += line.height() * interval;
        } else {
            line.setPosition(QPointF(0, cursorY));
            cursorY += line.height() * interval;
        }
    }

    textLayout.endLayout();

    if (vertical) {
        textLayout.draw(p, QPoint(0, 0)); // Для вертикального текста
        p->drawRect(QRect(0, 0, rctPaint.width(), rctPaint.height()));
    } else {
        textLayout.draw(p, QPoint(rctPaint.x(), rctPaint.y())); // Для горизонтального текста
        p->drawRect(rctPaint);
    }

    p->restore();
}

double PrintPage::singleRow()
{
    int size = m_fontTitle.pointSize() * 1.2;
    if(size % 2)
        size++;
    return size;
}
