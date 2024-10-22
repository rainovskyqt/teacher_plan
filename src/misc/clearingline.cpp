#include "clearingline.h"

#include <QIntValidator>

ClearingLine::ClearingLine(QWidget *parent) : QLineEdit(parent) {
    setValidator(new QIntValidator(0, 1512, this));

    connect(this, &QLineEdit::textEdited, this, [this](const QString &text){
        setNum(text.toInt());
    });
}

void ClearingLine::setNum(const int num)
{
    QString val = num ? QString::number(num) : "";
    QLineEdit::setText(val);

    emit valueChanged();
}
