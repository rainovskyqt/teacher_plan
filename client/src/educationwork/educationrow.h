#ifndef EDUCATIONROW_H
#define EDUCATIONROW_H

#include <QWidget>

namespace Ui {
class EducationRow;
}

class EducationalWork;

class EducationRow : public QWidget
{
    Q_OBJECT

public:
    explicit EducationRow(int row, EducationalWork *work, QWidget *parent = nullptr);
    ~EducationRow();
    void setData(EducationalWork *work);

    QString toString();

    EducationalWork *work() const;

private slots:
    void on_btn_deleteRow_clicked();
    void countHours();

signals:
    void deleteWork();
    void saveWork(EducationalWork*);

private:
    Ui::EducationRow *ui;

    EducationalWork *m_work;

    void loadDictionaries();
    void makeConnections();
    void makeHoursConnections();
    void countPlanHours();
    void countFacticalHours();
    void countYearPlan();
    void countYearFactical();
};

#endif // EDUCATIONROW_H
