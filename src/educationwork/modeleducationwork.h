#ifndef MODELEDUCATIONWORK_H
#define MODELEDUCATIONWORK_H

#include <QStandardItemModel>

#include "educationwork.h"

class QSqlQuery;

class ModelEducationWork : public QStandardItemModel
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

    explicit ModelEducationWork(QObject *parent = nullptr);
    void loadData(int planId);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void deleteWork(int id);
    // void saveMainData()

public slots:

private:
    void addData(QSqlQuery *query);
};

#endif // MODELEDUCATIONWORK_H
