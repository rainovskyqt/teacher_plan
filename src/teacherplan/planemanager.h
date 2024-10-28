#ifndef PLANEMANAGER_H
#define PLANEMANAGER_H

#include <QObject>
#include "teacherplan.h"

class PlaneManager : public QObject
{
    Q_OBJECT
public:
    explicit PlaneManager(QObject *parent = nullptr);
    static PlaneManager *get();
    int planByStaff(int staffId);
    TeacherPlan *staffPlan(int staff);
};

#endif // PLANEMANAGER_H
