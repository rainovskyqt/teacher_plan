#ifndef PAGESTUDY_H
#define PAGESTUDY_H

#include "printpage.h"

class PageStudy : public PrintPage
{
    Q_OBJECT
public:
    explicit PageStudy(int wigth, int height, int coefficient, QWidget *parent = nullptr);
    void setData(PrintData *data) override;

private:
    void paintData(QPainter &painter) override;

protected:
    void setRects() override;
};

#endif // PAGESTUDY_H
