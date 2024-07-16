#ifndef MONTH_H
#define MONTH_H

#include <QMap>
#include <QObject>

class Month : public QObject
{
    Q_OBJECT
public:

    enum Months{
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

    explicit Month(QObject *parent = nullptr);

    QString name(Months month);

signals:

private:
    QMap<Months, QString> m_months;

};

#endif // MONTH_H
