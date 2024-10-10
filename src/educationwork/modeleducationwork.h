#ifndef MODELEDUCATIONWORK_H
#define MODELEDUCATIONWORK_H

#include <QSqlQueryModel>

class ModelEducationWork : public QSqlQueryModel
{
public:

    enum Fields{
        WorkId,
        DisciplineId,
        CourseId,
        WorkFormId,
        GroupCount,
        Comments,
        OrderPalce,
        Hours
    };

    enum HourFields{
        HourId,
        HourWeek,
        HourType,
        HourValue
    };

    struct Hour{
        int id;
        int week;
        int type;
        int value;
    };

    struct EducationWork{
        int id;
        int disciplineId;
        int courseId;
        int workFormId;
        int groupCount;
        QString comments;
        int orderPalce;
        QHash<int, Hour> hours;
    };


    explicit ModelEducationWork(QObject *parent = nullptr);
    void loadData(int planeId);

    QVector<EducationWork> works() const;

    void deleteWork(int id);

public slots:

private:    
    QHash<int, Hour> splitHours(const QString &hoursString) const;
};

#endif // MODELEDUCATIONWORK_H
