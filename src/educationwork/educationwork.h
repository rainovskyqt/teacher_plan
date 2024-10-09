#ifndef EDUCATIONWORK_H
#define EDUCATIONWORK_H

#include <QHash>
#include <QObject>

class Hour : public QObject
{
    Q_OBJECT

public:
    enum HourTypes{
        Plane,
        Factical
    };

    enum HourFields{
        HourId,
        HourWeek,
        HourType,
        HourValue
    };

    Hour(int id, int week, int type, int value, QObject *parent);

    int id() const;
    int week() const;
    int type() const;
    int value() const;
    void setValue(int newValue);

signals:
    void valueChanged(int, int, int);

private:
    const int m_id;
    const int m_week;
    const int m_type;
    int m_value;
};

//========================= EducationWork =========================
class EducationWork : public QObject
{
    Q_OBJECT
public:
    EducationWork(int id, int discipline, int course, int workForm, int groupCount,
                  const QString &comments, int orderPlace, const QString &hours, QObject *parent = nullptr);
    QHash<int, Hour*> splitHours(const QString &hoursString);

    int id() const;

    int disciplineId() const;
    int courseId() const;
    int workFormId() const;
    int groupCount() const;
    QString comments() const;
    int orderPalce() const;
    QHash<int, Hour *> hours() const;

    void setDisciplineId(int newDisciplineId);
    void setCourseId(int newCourseId);
    void setWorkFormId(int newWorkFormId);
    void setGroupCount(int newGroupCount);
    void setComments(const QString &newComments);
    void setOrderPalce(int newOrderPalce);

signals:

private:
    int m_id;
    int m_disciplineId;
    int m_courseId;
    int m_workFormId;
    int m_groupCount;
    QString m_comments;
    int m_orderPalce;
    QHash<int, Hour*> m_hours;
};

Q_DECLARE_METATYPE(EducationWork*)

#endif // EDUCATIONWORK_H
