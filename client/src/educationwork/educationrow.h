#ifndef EDUCATIONROW_H
#define EDUCATIONROW_H

#include <QWidget>
#include <misc/month.h>
#include "educationalhour.h"
#include "database/models/teacherwork.h"

namespace Ui {
class EducationRow;
}

class EducationalWork;

using S = TeacherWork::Status;

class EducationRow : public QWidget
{
    Q_OBJECT

public:
    explicit EducationRow(int row, EducationalWork *work = nullptr,
                          S status = S::Development, QWidget *parent = nullptr);
    ~EducationRow();
    void setData(EducationalWork *work);
    QString toString();

    EducationalWork *work() const;
    int getTime(EducationalHour::HourType type, int week);
    void loadHours();

    int row();
    void setRow(int row);

public slots:
    void setScrolBarValue(int val);

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
    bool readySave;
    TeacherWork::Status m_status;

    void setStatus(S status);
    void addMonths(S status);

    void loadDictionaries();
    void makeConnections();

    void saveHour(EducationalHour *hour);
    void setNewWorkId(int id);

    void colorRow(bool accepted);
};

#endif // EDUCATIONROW_H
