#ifndef PLANEMANAGER_H
#define PLANEMANAGER_H

#include <QObject>

class PlaneManager : public QObject
{
    Q_OBJECT
public:
    explicit PlaneManager(QObject *parent = nullptr);
    static PlaneManager *get();
    int planByStaff(int staffId);

};

#endif // PLANEMANAGER_H
