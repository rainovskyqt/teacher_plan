#include "delegateeducationwork.h"
#include "roweducationwork.h"

#include <QPainter>
#include <QDebug>

using EM = ModelEducationWork;

DelegateEducationWork::DelegateEducationWork(QObject *parent) :
    QStyledItemDelegate(parent) {}

QWidget *DelegateEducationWork::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    RowEducationWork *editor = new  RowEducationWork(index.row() + 1, parent);
    // editor->setSelected();
    return editor;
}

void DelegateEducationWork::setEditorData(QWidget *editor, const QModelIndex &index) const {
    RowEducationWork *rowEditor = static_cast<RowEducationWork *>(editor);
    EducationWork *work = index.data(EM::EducationData).value<EducationWork *>();
    if (work) {
        rowEditor->setWorkData(work);
    }
}

void DelegateEducationWork::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    // RowEducationWork *rowEditor = static_cast<RowEducationWork *>(editor);
    EducationWork *work = index.data(EM::EducationData).value<EducationWork *>();
    if (work) {
        // model->setData(index, QVariant::fromValue(work), Qt::UserRole);
    }
}

void DelegateEducationWork::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    EducationWork *work = index.data(Qt::UserRole).value<EducationWork *>();
    if (work) {
        RowEducationWork row(index.row() + 1);
        // row.setWorkData(work);

        painter->save();
        painter->translate(option.rect.topLeft() - QPoint(0, 0));  // смещаем отображение по горизонтали
        row.render(painter);
        painter->restore();
    }

    // if (index.data(EM::Pixmap).canConvert<QPixmap>()) {
    //     QPixmap cachedPixmap = index.data(EM::Pixmap).value<QPixmap>();
    //     qDebug() << "cachedPixmap" << cachedPixmap;
    //     painter->drawPixmap(option.rect, cachedPixmap);
    // } else {
    //     QPixmap pixmap(option.rect.size());
    //     pixmap.fill(Qt::transparent);
    //     QPainter pixmapPainter(&pixmap);

    //     EducationWork *work = index.data(EM::EducationData).value<EducationWork *>();
    //     if (work) {
    //         RowEducationWork row(index.row() + 1);
    //         row.setWorkData(work);

    //         // painter->save();
    //         pixmapPainter.translate(option.rect.topLeft());  // смещаем отображение по горизонтали
    //         row.render(&pixmapPainter);
    //         // painter->restore();

    //         // QModelIndex mutableIndex = index;
    //         // mutableIndex.model()->setData(mutableIndex, QVariant::fromValue(pixmap), Qt::UserRole + 1);

    //         QAbstractItemModel *model = const_cast<QAbstractItemModel*>(index.model());
    //         model->setData(index, QVariant::fromValue(pixmap), EM::Pixmap);
    //         qDebug() << "Пишем в индекс:" << index << " pixmap:" << pixmap;
    //         painter->drawPixmap(option.rect, pixmap);
    //     }
    // }
}

QSize DelegateEducationWork::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return RowEducationWork::rowSize();
}
