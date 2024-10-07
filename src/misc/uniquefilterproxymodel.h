#ifndef UNIQUEFILTERPROXYMODEL_H
#define UNIQUEFILTERPROXYMODEL_H

#include <QSet>
#include <QSortFilterProxyModel>

class UniqueFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit UniqueFilterProxyModel(QObject *parent = nullptr);

    void setSourceColumn(int column);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    void invalidateFilter();

private:
    mutable QSet<QString> uniqueValues;
    int m_sourceColumn;
};


#endif // UNIQUEFILTERPROXYMODEL_H
