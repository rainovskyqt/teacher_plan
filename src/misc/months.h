#ifndef MONTHS_H
#define MONTHS_H

#include <QHash>
#include <QMap>
#include <QObject>

class Months : public QObject
{
    Q_OBJECT
public:

    enum Month{
        January = 1,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September = 9,
        October,
        November,
        December,
        Other
    };

    explicit Months(QObject *parent = nullptr);

    static Months *get();
    QString name(Month month) const;
    QList<Month> educationYearList() const;
    bool isFirstSemester(Month month) const;
    QPair<int, int> monthWeeks(Month month) const;
    QPair<int, int> weekDates(int week) const;

    void loadSettings(int year);

signals:

private:
    QHash<Month, QPair<int, int>> m_monthWeeks;
    QHash<int, QPair<int, int>> m_weeksDates;

};

#endif // MONTHS_H
