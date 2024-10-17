#include "emptylbl.h"

EmptyLbl::EmptyLbl(QWidget *parent) : QLabel(parent) {}

void EmptyLbl::setNum(int num)
{
    if(num != 0)
        QLabel::setNum(num);
    else
        QLabel::setText("");
}
