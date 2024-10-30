#ifndef MODELGENERICWORK_H
#define MODELGENERICWORK_H

#include <QObject>

class ModelGenericWork;

class ModelGenericWork : public QObject
{
public:

    // enum class Fields{
    //     WorkId,
    //     DisciplineId,
    //     CourseId,
    //     WorkFormId,
    //     GroupCount,
    //     Comments,
    //     OrderPalce,
    //     Hours
    // };

    // enum class HourFields{
    //     HourId,
    //     HourWeek,
    //     HourPlanValue,
    //     HourFactValue
    // };

    // enum class HourType{
    //     Plane = 1,
    //     Factical
    // };

    explicit ModelGenericWork(QObject *parent = nullptr);
    // QList<EducationWork*> loadData(int planeId);
    // void saveHours(EducationWork*w, int week);
    // void deleteWork(int id);
    // void saveWork(EducationWork *w);

private:    
};

#endif // MODELGENERICWORK_H
