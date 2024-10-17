#ifndef MODELEDUCATIONWORK_H
#define MODELEDUCATIONWORK_H

#include <QSqlQueryModel>

class ModelEducationWork : public QSqlQueryModel
{
public:

    enum class Fields{
        WorkId,
        DisciplineId,
        CourseId,
        WorkFormId,
        GroupCount,
        Comments,
        OrderPalce,
        Hours
    };

    enum class HourFields{
        HourId,
        HourWeek,
        HourType,
        HourValue
    };

    struct Hour{
        int id;
        int week;
        int planValue;
        int factValue;
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
    void deleteWork(int id);

    QHash<int, Hour> hours(int row) const;

public slots:
    void updateValues(Hour hour);

private:    
};

#endif // MODELEDUCATIONWORK_H
