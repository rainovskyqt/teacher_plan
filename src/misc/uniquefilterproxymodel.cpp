#include "uniquefilterproxymodel.h"

UniqueFilterProxyModel::UniqueFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

void UniqueFilterProxyModel::setSourceColumn(int column)
{
    m_sourceColumn = column;
}

bool UniqueFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, m_sourceColumn, sourceParent);
    QString value = sourceModel()->data(index).toString();

    if (!uniqueValues.contains(value)) {
        uniqueValues.insert(value);
        return true;
    }
    return false;
}

void UniqueFilterProxyModel::invalidateFilter() {
    QSortFilterProxyModel::invalidateFilter();
    uniqueValues.clear();
}
