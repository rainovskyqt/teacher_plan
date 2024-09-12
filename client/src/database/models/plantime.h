#ifndef PLANTIME_H
#define PLANTIME_H

#include <QJsonObject>
#include <QObject>

class PlanTime : public QObject
{
    Q_OBJECT
public:

    enum WorkType{
        Educational,
        MethodicWork,
        SearchingWork,
        SportWork,
        OtherWork,
        Total,
        ElementsCount = 6
    };

    enum Semester{
        FirstSemester = 1,
        SecondSemestr
    };

    explicit PlanTime(int workType,
                      QString name,
                      int firstSemesterHours = 0,
                      int secondSemesterHours = 0,
                      int baseId = 0,
                      int orderPlace = 0,
                      QObject *parent = nullptr);

    static int maxHoursCount(WorkType type);

    QString name() const;
    int semesterHours(Semester semester) const;
    void setSemesterHours(int semesterHours, Semester semester);
    QString romanNumeral(int number);

    int workType() const;
    void setWorkType(int newWorkType);

    int baseId() const;
    void setBaseId(int newBaseId);

signals:

private:
    int m_baseId;
    int m_planId;
    int m_workType;
    QString m_name;
    int m_firstSemesterHours;
    int m_secondSemesterHours;
    int m_orderPlace;

    QString toRomanNumeral(int numeral);
};

#endif // PLANTIME_H
