#include "modeleducationwork.h"

#include <QDebug>

#include "database/database.h"

ModelEducationWork::ModelEducationWork(QObject *parent)
    : QStandardItemModel{parent}
{}

void ModelEducationWork::loadData(int planId)
{
    clear();
    QString queryString = R"(SELECT EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place,
                          GROUP_CONCAT(CONCAT(EWH.id,',', EWH.`week`,',', EWH.`type`,',', EWH.`value`) SEPARATOR ';') AS hours
                          FROM educational_work EW
                          INNER JOIN teacher_plan TP ON TP.id = EW.teacher_plan_id
                          LEFT JOIN educational_work_hours EWH ON EWH.plan_work_id = EW.id
                          WHERE TP.id = :planId
                          GROUP BY EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place
                          ORDER BY EW.order_place)";

    Arguments args;
    args.insert(":planId", planId);

    auto query = Database::get()->selectQuery(queryString, args);
    addData(&query);
}

QVariant ModelEducationWork::data(const QModelIndex &index, int role) const {
    return QStandardItemModel::data(index, role);
}

void ModelEducationWork::deleteWork(int id)
{

}

void ModelEducationWork::addData(QSqlQuery *query) {
    using F = Fields;
    while (query->next()) {

        EducationWork *work = new EducationWork(
            query->value(F::WorkId).toInt(),
            query->value(F::DisciplineId).toInt(),
            query->value(F::CourseId).toInt(),
            query->value(F::WorkFormId).toInt(),
            query->value(F::GroupCount).toInt(),
            query->value(F::Comments).toString(),
            query->value(F::OrderPalce).toInt(),
            query->value(F::Hours).toString()
            );

        QStandardItem *item = new QStandardItem();
        item->setData(QVariant::fromValue(work), Qt::UserRole);
        appendRow(item);
    }
}
