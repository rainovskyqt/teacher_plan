#include "delegateeducationwork.h"
#include "roweducationwork.h"

#include <QPainter>
#include <QDebug>

DelegateEducationWork::DelegateEducationWork(QObject *parent) :
    QStyledItemDelegate(parent) {}

QWidget *DelegateEducationWork::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return new RowEducationWork(index.row() + 1, parent);
}

void DelegateEducationWork::setEditorData(QWidget *editor, const QModelIndex &index) const {
    RowEducationWork *rowEditor = static_cast<RowEducationWork *>(editor);
    EducationWork *work = index.data(Qt::UserRole).value<EducationWork *>();
    if (work) {
        rowEditor->setWorkData(work);
    }
}

void DelegateEducationWork::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    // RowEducationWork *rowEditor = static_cast<RowEducationWork *>(editor);
    EducationWork *work = index.data(Qt::UserRole).value<EducationWork *>();
    if (work) {
        // model->setData(index, QVariant::fromValue(work), Qt::UserRole);
    }
    qDebug() << "setModelData";
}

void DelegateEducationWork::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    EducationWork *work = index.data(Qt::UserRole).value<EducationWork *>();
    if (work) {
        RowEducationWork row(index.row() + 1);
        row.setWorkData(work);

        painter->save();
        painter->translate(option.rect.topLeft() - QPoint(0, 0));  // смещаем отображение по горизонтали
        row.render(painter);
        painter->restore();
    }
}

QSize DelegateEducationWork::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return RowEducationWork::rowSize();
}
