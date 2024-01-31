#include "modeltotaltime.h"
#include <QVariant>
#include "database/database.h"
#include <QDebug>

ModelTotalTime::ModelTotalTime(QObject *parent)
    : QAbstractTableModel{parent}
{
    setHeaderModel();
    loadData();
}

int ModelTotalTime::rowCount(const QModelIndex &) const
{
    return m_hours.count() + 1;
}

int ModelTotalTime::columnCount(const QModelIndex &) const
{
    return PlanTime::elementsCount() + 1;
}

QVariant ModelTotalTime::data(const QModelIndex &index, int role) const {

    if(role==HierarchicalHeaderView::HorizontalHeaderDataRole){
        QVariant v;
        v.setValue((QObject*)&m_horizontalHeaderModel);
        return v;
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        qDebug() << m_hours.count();

        if(index.row() == m_hours.count()){
            switch(index.column()) {
            case 1:
                return QVariant("Всего за учебный год:");
            case 2:
                return QVariant(1);
            case 3:
                return QVariant(2);
            case 4:
                return QVariant(3);
            default:
                return QVariant();
            }
        }

        switch (index.column()) {
        case 0:
            return QVariant(m_hours.at(index.row())->romanNumeral());
        case 1:
            return QVariant(m_hours.at(index.row())->name());
        case 2:
            return QVariant(m_hours.at(index.row())->firstSemesterHours());
        case 3:
            return QVariant(m_hours.at(index.row())->secondSemesterHours());
        case 4:
            return QVariant(m_hours.at(index.row())->firstSemesterHours() + m_hours.at(index.row())->secondSemesterHours());
        default:
            return QVariant(0);
        }
    }

    return QVariant();
}

Qt::ItemFlags ModelTotalTime::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if ((index.column() == 2 || index.column() == 3) && index.row() < m_hours.count() ) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool ModelTotalTime::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        switch (index.column()) {
        case 2:
            m_hours.at(index.row())->setFirstSemesterHours(value.toInt());
            return true;
        case 3:
            m_hours.at(index.row())->setSecondSemesterHours(value.toInt());
            return true;
        }
    }
    return true;
}

void ModelTotalTime::setHeaderModel()
{
    QStandardItem* item = new QStandardItem("\t№\nп/п\t");
    m_horizontalHeaderModel.setItem(0, 0, item);

    item = new QStandardItem("\tНаименование вида работ\t");
    m_horizontalHeaderModel.setItem(0, 1, item);

    item = new QStandardItem("\tПлановое количество часов\t");

    item->appendColumn(QList<QStandardItem*>() << new QStandardItem("\tI-е полугодие\t"));
    item->appendColumn(QList<QStandardItem*>()<< new QStandardItem("\tII-е полугодие\t"));
    item->appendColumn(QList<QStandardItem*>()<< new QStandardItem("\tВсего за год\t"));

    m_horizontalHeaderModel.setItem(0, 2, item);
}

void ModelTotalTime::loadData()
{
    m_hours = Database::instance().getTotaTimeList();
}
