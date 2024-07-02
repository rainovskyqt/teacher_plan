#ifndef GENERICFOOTER_H
#define GENERICFOOTER_H

#include <QWidget>

namespace Ui {
class GenericFooter;
}

class GenericFooter : public QWidget
{
    Q_OBJECT

public:
    explicit GenericFooter(QWidget *parent = nullptr);
    ~GenericFooter();

public slots:
    void setPosition(int val);

private:
    Ui::GenericFooter *ui;
};

#endif // GENERICFOOTER_H
