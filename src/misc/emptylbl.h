#ifndef EMPTYLBL_H
#define EMPTYLBL_H

#include <QLabel>

class EmptyLbl : public QLabel
{
public:
    explicit EmptyLbl(QWidget *parent = nullptr);

    void setNum(int num);
};

#endif // EMPTYLBL_H
