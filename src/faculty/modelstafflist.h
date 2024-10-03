#ifndef MODELSTAFFLIST_H
#define MODELSTAFFLIST_H

#include <QStandardItemModel>

class ModelStaffList : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ModelStaffList();

    void loadStaff(int facultyId);
    QModelIndex getUserIndex(int userId, int departmentId);
    QStandardItem *getItem(QStandardItem *parent, int id);
};

#endif // MODELSTAFFLIST_H
