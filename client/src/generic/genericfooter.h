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

    int totalPlane() const;
    int totalFact() const;

public slots:
    void setPosition(int val);
    void setValues(int plan, int fact);

private:
    Ui::GenericFooter *ui;
};

#endif // GENERICFOOTER_H
