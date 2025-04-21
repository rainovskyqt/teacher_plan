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

    int totalFirstPlane();
    int totalFirstFact();
    int totalSecondPlane();
    int totalSecondFact();
    int totalYearPlane();
    int totalYearFact();

signals:
    void firstPlaneChanged(int);
    void secondPlaneChanged(int);
    void firstFacticalChanged(int);
    void secondFacticalChanged(int);

private:
    Ui::EducationalFooter *ui;

    void addMonths();
    void countHours(EducationalHour::HourType type);
};

#endif // EDUCATIONALFOOTER_H
