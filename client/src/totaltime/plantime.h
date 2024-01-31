#ifndef PLANTIME_H
#define PLANTIME_H

#include <QObject>

class PlanTime : public QObject
{
    Q_OBJECT
public:
    explicit PlanTime(QString romanNumeral,
                      QString name,
                      int firstSemesterHours = 0,
                      int secondSemesterHours = 0,
                      int baseId = 0,
                      QObject *parent = nullptr);

    static int maxHoursCount(double rate);
    static int elementsCount();

    QString romanNumeral() const;
    void setRomanNumeral(const QString &newRomanNumeral);
    QString name() const;
    void setName(const QString &newName);
    int firstSemesterHours() const;
    void setFirstSemesterHours(int newFirstSemesterHours);
    int secondSemesterHours() const;
    void setSecondSemesterHours(int newSecondSemesterHours);

signals:

private:
    int m_baseId;
    QString m_romanNumeral;
    QString m_name;
    int m_firstSemesterHours;
    int m_secondSemesterHours;
};

#endif // PLANTIME_H
