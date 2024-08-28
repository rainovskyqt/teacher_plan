#ifndef EDUCATIONALFOOTER_H
#define EDUCATIONALFOOTER_H

#include "educationalhour.h"

#include <QWidget>

namespace Ui {
class EducationalFooter;
}

class EducationalFooter : public QWidget
{
    Q_OBJECT

public:
    explicit EducationalFooter(QWidget *parent = nullptr);
    ~EducationalFooter();

    void setPosition(int val);
    void setValue(EducationalHour *hour);
    void setTotalValue(int value, QString name);
    void clear();

signals:
    void firstPlaneChanget(int);
    void secondPlaneChanget(int);
    void firstFacticalChanget(int);
    void secondFacticalChanget(int);

private:
    Ui::EducationalFooter *ui;

    void addMonths();
    void countHours(EducationalHour::HourType type);
};

#endif // EDUCATIONALFOOTER_H
