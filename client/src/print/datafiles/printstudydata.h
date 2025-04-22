#ifndef PRINTSTUDYDATA_H
#define PRINTSTUDYDATA_H

#include "printdata.h"

class PrintStudyWork : public QObject
{
    Q_OBJECT
public:
    explicit PrintStudyWork(int position, QString name,int totalPlaneI, int totalFactI, int totalPlaneII,int totalFactII,
                            int totalPlaneYear, int totalFactYear, QString comments, QObject *parent = nullptr);

    int position() const;
    QString name() const;
    int totalPlaneI() const;
    int totalFactI() const;
    int totalPlaneII() const;
    int totalFactII() const;
    int totalPlaneYear() const;
    int totalFactYear() const;

    QMap<int, QPair<int, int> > hours() const;
    void addHours(int week, int plane, int fact);

    QString comments() const;
    void setComments(const QString &newComments);

private:
    int m_position;
    QString m_name;
    int m_totalPlaneI;
    int m_totalFactI;
    int m_totalPlaneII;
    int m_totalFactII;
    int m_totalPlaneYear;
    int m_totalFactYear;
    QString m_comments;

    QMap<int, QPair<int, int>> m_hours;
};

class PrintStudyData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintStudyData(QObject *parent = nullptr);

    int totalYearPlane() const;
    void setTotalYearPlane(int newTotalYearPlane);
    int totalYearFact() const;
    void setTotalYearFact(int newTotalYearFact);
    QMap<int, QPair<int, int> > weekTotal() const;
    void addWeekTotal(int week, int plane, int fact);

    void addWork(int position, PrintStudyWork *work);

    int totalFirstPlane() const;
    void setTotalFirstPlane(int newTotalFirstPlane);
    int totalFirstFact() const;
    void setTotalFirstFact(int newTotalFirstFact);

    int totalSecondPlane() const;
    void setTotalSecondPlane(int newTotalSecondPlane);
    int totalSecondFact() const;
    void setTotalSecondFact(int newTotalSecondFact);

    QMap<int, PrintStudyWork *> works() const;

private:
    int m_totalFirstPlane;
    int m_totalFirstFact;
    int m_totalSecondPlane;
    int m_totalSecondFact;
    int m_totalYearPlane;
    int m_totalYearFact;

    QMap<int, QPair<int, int>> m_weekTotal;
    QMap<int, PrintStudyWork*> m_works;

};

#endif // PRINTSTUDYDATA_H
