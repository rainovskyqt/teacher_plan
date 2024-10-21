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

    enum class HourType{
        Plane = 1,
        Factical
    };

    struct Hour{
        int week;
        int planId;
        int planValue;
        int factId;
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

Q_DECLARE_METATYPE(ModelEducationWork::HourType)

#endif // MODELEDUCATIONWORK_H
