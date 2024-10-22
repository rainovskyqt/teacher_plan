#ifndef CLEARINGLINE_H
#define CLEARINGLINE_H

#include <QLineEdit>

class ClearingLine : public QLineEdit
{
    Q_OBJECT
public:
    explicit ClearingLine(QWidget *parent = nullptr);

    void setNum(const int num);

signals:
    void valueChanged();
};

#endif // CLEARINGLINE_H
