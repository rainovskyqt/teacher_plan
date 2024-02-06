#include "modeltotaltime.h"
#include <QVariant>
#include "database/database.h"
#include <QDebug>

ModelTotalTime::ModelTotalTime(QObject *parent)
    : QAbstractTableModel{parent}
    , m_rate{1}
{
    setHeaderModel();
    loadData();

}

int ModelTotalTime::rowCount(const QModelIndex &) const
{
    return Rows::ElementsCount;
}

int ModelTotalTime::columnCount(const QModelIndex &) const
{
    return Columns::ElementsCount;
}

QVariant ModelTotalTime::data(const QModelIndex &index, int role) const {

    if(role==HierarchicalHeaderView::HorizontalHeaderDataRole){
        QVariant v;
        v.setValue((QObject*)&m_horizontalHeaderModel);
        return v;
    }

    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    if(role == Qt::BackgroundRole){
        return color(index);
    }

    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {

        if(index.row() == m_hours.count()){
            return totalHours(index);
        }

        return currentHours(index);
    }

    return QVariant();
}

Qt::ItemFlags ModelTotalTime::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if ((index.column() == FirstSemester || index.column() == SecondSemester) && index.row() < m_hours.count() ) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool ModelTotalTime::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        switch (index.column()) {
        case FirstSemester:
            m_hours.at(index.row())->setSemesterHours(value.toInt(), PlanTime::FirstSemester);
            return true;
        case SecondSemester:
            m_hours.at(index.row())->setSemesterHours(value.toInt(), PlanTime::SecondSemestr);
            return true;
        }
    }
    return true;
}

void ModelTotalTime::setRate(double rate)
{
    m_rate = rate;
    emit dataChanged(this->index(Rows::Educational, Columns::Year), this->index(Rows::Total, Columns::Year));
}

QVariant ModelTotalTime::color(const QModelIndex &index) const
{
    if(index.column() != Columns::Year || (index.row() != Rows::Educational && index.row() != Rows::Total))
        return QVariant();

    int yearHours = data(this->index(index.row(), Columns::Year)).toInt();
    PlanTime::WorkType workType = static_cast<PlanTime::WorkType>(index.row());
    if(yearHours == PlanTime::maxHoursCount(workType) * m_rate)
        return QBrush(Qt::green);
    else if (yearHours > PlanTime::maxHoursCount(workType) * m_rate)
        return QBrush(Qt::red);

    return QVariant();
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
    item->appendColumn(QList<QStandardItem*>()<< new QStandardItem("\tНорма\t"));

    m_horizontalHeaderModel.setItem(0, 2, item);
}

void ModelTotalTime::loadData()
{
    m_hours = Database::instance()->getTotaTimeList();
}

QVariant ModelTotalTime::currentHours(const QModelIndex &index) const
{
    switch (index.column()) {
    case RomanNumber:
        return QVariant(m_hours.at(index.row())->romanNumeral());
    case Name:
        return QVariant(m_hours.at(index.row())->name());
    case FirstSemester:
        return QVariant(m_hours.at(index.row())->semesterHours(PlanTime::FirstSemester));
    case SecondSemester:
        return QVariant(m_hours.at(index.row())->semesterHours(PlanTime::SecondSemestr));
    case Year:
        return QVariant(m_hours.at(index.row())->semesterHours(PlanTime::FirstSemester) +
                        m_hours.at(index.row())->semesterHours(PlanTime::SecondSemestr));
    case Norma:
        if(index.row() == 0)
            return QVariant(QString("Не более: %1").arg(PlanTime::maxHoursCount(PlanTime::Educational) * m_rate));
        return QVariant();
    default:
        return QVariant();
    }
}

QVariant ModelTotalTime::totalHours(const QModelIndex &index) const
{
    switch(index.column()) {
    case Name:
        return QVariant("Всего за учебный год:");
    case FirstSemester:
        return QVariant(hoursCount(2));
    case SecondSemester:
        return QVariant(hoursCount(3));
    case Year:
        return QVariant(hoursCount(2) + hoursCount(3));
    case 5:
        if(index.row() == m_hours.count())
            return QVariant(QString("Ровно: %1").arg(PlanTime::maxHoursCount(PlanTime::Total) * m_rate));
        return QVariant();
    default:
        return QVariant();
    }
}

int ModelTotalTime::hoursCount(int column) const
{
    int count = 0;
    for(QVector<PlanTime*>::const_iterator it = m_hours.begin(); it != m_hours.end(); ++it){
        if(column == FirstSemester)
            count += (*it)->semesterHours(PlanTime::FirstSemester);
        else if (column == SecondSemester)
            count += (*it)->semesterHours(PlanTime::SecondSemestr);
    }
    return count;
}
