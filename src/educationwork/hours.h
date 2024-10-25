#ifndef HOURS_H
#define HOURS_H

#include <QObject>

class Hour : public QObject{

public:
    explicit Hour(QObject *parent = nullptr);

    int id() const;
    void setId(int newId);
    int week() const;
    void setWeek(int newWeek);
    int plan() const;
    void setPlan(int newPlan);
    int fact() const;
    void setFact(int newFact);

private:
    int m_id;
    int m_week;
    int m_plan;
    int m_fact;
};

class TotalHour : public QObject{

public:
    explicit TotalHour(QObject *parent = nullptr);
};

#endif // HOURS_H
