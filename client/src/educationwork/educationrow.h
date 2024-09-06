#ifndef EDUCATIONROW_H
#define EDUCATIONROW_H

#include <QWidget>
#include <misc/month.h>
#include "educationalhour.h"

namespace Ui {
class EducationRow;
}

class EducationalWork;

class EducationRow : public QWidget
{
    Q_OBJECT

public:
    explicit EducationRow(int row, EducationalWork *work = nullptr, QWidget *parent = nullptr);
    ~EducationRow();
    void setData(EducationalWork *work);
    QString toString();

    EducationalWork *work() const;
    int getTime(EducationalHour::HourType type, int week);
    void loadHours();

private slots:
    void countHours(EducationalHour::HourType type);

signals:
    void deleteWork();
    void saveWork(EducationalWork*);
    void valueChanged(EducationalHour*);
    void factValueChanged(Month::Months, int, int);

private:
    Ui::EducationRow *ui;

    EducationalWork *m_work;

    void addMonths();

    void loadDictionaries();
    void makeConnections();

    void saveHour(EducationalHour *hour);
    bool readySave;
};

#endif // EDUCATIONROW_H
