#ifndef TOTALTIMELIST_H
#define TOTALTIMELIST_H

#include <QObject>

class TotalTimeList : public QObject
{
    Q_OBJECT
public:
    explicit TotalTimeList(QObject *parent = nullptr);

    int maxHoursCount() const;

public slots:
    void setTime();

signals:
    void timeChange(bool valid);

private:
    const int m_maxHoursCount;
};

//===========================================================

class PlanTime: public QObject
{
    enum WorkType{
        StudyWork = 1,
        MethodicWork,
        SearchingWork,
        SportWork,
        OtherWork
    };

    explicit PlanTime(int id, int workType, bool firstHalf, int count);

};

#endif // TOTALTIMELIST_H
