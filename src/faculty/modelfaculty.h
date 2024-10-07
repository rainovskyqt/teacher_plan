#ifndef MODELFACULTY_H
#define MODELFACULTY_H

#include <QStandardItemModel>

#include "staff/modelstafflist.h"

class ModelFaculty : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit ModelFaculty(QObject *parent = nullptr);

    void setSourceModel(ModelStaffList *newSourceModel);
    void loadByDepartment(int year, int departmentId);

    QModelIndex getUserIndex(int userId, int departmentId);
    QStandardItem *getItem(QStandardItem *parent, int id);

private:
    ModelStaffList *m_sourceModel;
    void populate();
};

#endif // MODELFACULTY_H
