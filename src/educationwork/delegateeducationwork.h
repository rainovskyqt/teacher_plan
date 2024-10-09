#ifndef DELEGATEEDUCATIONWORK_H
#define DELEGATEEDUCATIONWORK_H

#include <QObject>
#include <QStyledItemDelegate>

class DelegateEducationWork : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DelegateEducationWork(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATEEDUCATIONWORK_H
