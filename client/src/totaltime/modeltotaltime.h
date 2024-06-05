#ifndef MODELTOTALTIME_H
#define MODELTOTALTIME_H

#include <QAbstractTableModel>
#include <QStandardItemModel>

#include <database/models/teacherplan.h>

#include "../misc/HierarchicalHeaderView.h"
#include "database/models/plantime.h"

class ModelTotalTime : public QAbstractTableModel
{

public:
    explicit ModelTotalTime(QObject *parent = nullptr);

    int rowCount(const QModelIndex& /*parent*/) const override;
    int columnCount(const QModelIndex& /*parent*/) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void setRate(double rate);
    void setHours(TeacherPlan *plan);

public slots:
    void reset();

private:
    using Rows = PlanTime::WorkType;
    enum Columns{
        RomanNumber,
        Name,
        FirstSemester,
        SecondSemester,
        Year,
        Norma,
        ElementsCount = 6
    };

    QStandardItemModel m_horizontalHeaderModel;
    QVector<PlanTime*> m_hours;
    double m_rate;

    QVariant color(const QModelIndex &index) const;
    void setHeaderModel();
    void setDefaulFields();
    QVariant currentHours(const QModelIndex &index) const;
    QVariant totalHours(const QModelIndex &index) const;
    int hoursCount(int column) const;
};

#endif // MODELTOTALTIME_H
