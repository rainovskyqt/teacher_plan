#include "modeleducationwork.h"

#include <QDebug>

#include "database/database.h"

ModelEducationWork::ModelEducationWork(QObject *parent)
    : QSqlQueryModel{parent}
{}

void ModelEducationWork::loadData(int staffId)
{
    QString queryString = R"(SELECT EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place,
                          GROUP_CONCAT(CONCAT(EWH.id,',', EWH.`week`,',', EWH.`type`,',', EWH.`value`) SEPARATOR ';') AS hours
                          FROM educational_work EW
                          INNER JOIN teacher_plan TP ON TP.id = EW.teacher_plan_id
                          INNER JOIN staff S ON TP.staff_id = S.id
                          LEFT JOIN educational_work_hours EWH ON EWH.plan_work_id = EW.id
                          WHERE S.id = :staffId
                          GROUP BY EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place
                          ORDER BY EW.order_place)";

    Arguments args;
    args.insert(":staffId", staffId);

    auto query = Database::get()->selectQuery(queryString, args);
    setQuery(query);
}

QVector<ModelEducationWork::EducationWork> ModelEducationWork::works() const
{
    QVector<EducationWork> works;

    for(int row = 0; row < rowCount(); ++row){
        works.append(EducationWork(
            data(index(row, WorkId)).toInt(),
            data(index(row, DisciplineId)).toInt(),
            data(index(row, CourseId)).toInt(),
            data(index(row, WorkFormId)).toInt(),
            data(index(row, GroupCount)).toInt(),
            data(index(row, Comments)).toString(),
            data(index(row, OrderPalce)).toInt(),
            splitHours(data(index(row, Hours)).toString())
            ));
    }

    return works;
}

void ModelEducationWork::deleteWork(int id)
{

}

QHash<int, ModelEducationWork::Hour> ModelEducationWork::splitHours(const QString &hoursString) const
{
    QHash<int, ModelEducationWork::Hour> hours;
    QStringList splittedHours = hoursString.split(";", Qt::SkipEmptyParts);
    for(const QString &hourRow : qAsConst(splittedHours)){
        QStringList h = hourRow.split(",");
        hours.insert(h.at(HourWeek).toInt(), {h.at(HourId).toInt(),
                                                 h.at(HourWeek).toInt(),
                                                 h.at(HourType).toInt(),
                                                 h.at(HourValue).toInt()
                                             });
    }
    return hours;
}
