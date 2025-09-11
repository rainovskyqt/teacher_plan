#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include <QObject>

class Staff;

class StaffManager : public QObject
{
    Q_OBJECT
public:
    explicit StaffManager(QObject *parent = nullptr);

    static StaffManager *get();

    void saveStaff(int userId, Staff staff);
    void deleteStaff(int staffId);
    Staff *getStaff(int staffId);

signals:
};

#endif // STAFFMANAGER_H
