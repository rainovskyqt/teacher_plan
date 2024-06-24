#ifndef MODELEDUCATIONWORK_H
#define MODELEDUCATIONWORK_H

#include <QAbstractTableModel>

class ModelEducationWork : public QAbstractTableModel
{
public:
    explicit ModelEducationWork(QObject *parent = nullptr);

    int rowCount(const QModelIndex& /*parent*/) const override;
    int columnCount(const QModelIndex& /*parent*/) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

};

#endif // MODELEDUCATIONWORK_H
