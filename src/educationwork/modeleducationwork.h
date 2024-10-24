#ifndef MODELEDUCATIONWORK_H
#define MODELEDUCATIONWORK_H

#include <QObject>

class EducationWork;

class ModelEducationWork : public QObject
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
        HourPlanValue,
        HourFactValue
    };

    enum class HourType{
        Plane = 1,
        Factical
    };

    explicit ModelEducationWork(QObject *parent = nullptr);
    QList<EducationWork*> loadData(int planeId);
    void saveHours(EducationWork*w, int week);
    void deleteWork(int id);


public slots:
    // void updateValues(Hour hour);

private:    
};

Q_DECLARE_METATYPE(ModelEducationWork::HourType)

#endif // MODELEDUCATIONWORK_H
