#ifndef EDUCATIONALHOUR_H
#define EDUCATIONALHOUR_H

#include <QObject>

class EducationalHour : public QObject
{
    Q_OBJECT
public:

    enum HourType{
        Plane = 1,
        Factical
    };

    explicit EducationalHour(int baseId, int planeWorkId, int month, int week,
                             int value, HourType type, QObject *parent = nullptr);


    int baseId() const;
    int planeWorkId() const;
    int month() const;
    int week() const;
    int value() const;
    void setValue(int newValue);
    HourType type() const;

signals:

private:
    int m_baseId;
    int m_planeWorkId;
    int m_month;
    int m_week;
    int m_value;
    HourType m_type;
};

#endif // EDUCATIONALHOUR_H
