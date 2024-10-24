#include "clearingline.h"

#include <QIntValidator>

ClearingLine::ClearingLine(QWidget *parent) : QLineEdit(parent) {
    setValidator(new QIntValidator(0, 1512, this));

    connect(this, &QLineEdit::editingFinished, this, [this](){
        setNum(this->text());
    });

    connect(this, &QLineEdit::textChanged, this, [this](const QString &text){
        if(text == "")
            setNum(0);
    });
}

void ClearingLine::setNum(const int num)
{
    QString str = QString::number(num);
    QString val = num ? str : "";
    QLineEdit::setText(val);

    if(str != m_original)
        emit valueChanged();
}

void ClearingLine::setNum(const QString &num)
{
    int val = num == "" ? 0 : num.toInt();
    setNum(val);
}

void ClearingLine::focusInEvent(QFocusEvent *e)
{
    m_original = this->text();
    QLineEdit::focusInEvent(e);
}
