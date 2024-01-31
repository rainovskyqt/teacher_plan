#ifndef MODELTOTALTIME_H
#define MODELTOTALTIME_H

#include <QAbstractTableModel>
#include <QStandardItemModel>

#include "../misc/HierarchicalHeaderView.h"
#include "plantime.h"

class ModelTotalTime : public QAbstractTableModel
{

public:
    explicit ModelTotalTime(QObject *parent = nullptr);

    int rowCount(const QModelIndex& /*parent*/) const override;
    int columnCount(const QModelIndex& /*parent*/) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex & index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    QStandardItemModel m_horizontalHeaderModel;
    QVector<PlanTime*> m_hours;

    void setHeaderModel();
    void loadData();
};

#endif // MODELTOTALTIME_H
