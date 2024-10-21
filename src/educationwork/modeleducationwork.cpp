#include "modeleducationwork.h"

#include <QDebug>

#include "database/database.h"

ModelEducationWork::ModelEducationWork(QObject *parent)
    : QSqlQueryModel{parent}
{}

void ModelEducationWork::loadData(int planeId)
{
    QString queryString = R"(SELECT EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place,
                          GROUP_CONCAT(CONCAT(EWH.id,',', EWH.`week`,',', EWH.`type`,',', EWH.`value`) SEPARATOR ';') AS hours
                          FROM educational_work EW
                          INNER JOIN teacher_plan TP ON TP.id = EW.teacher_plan_id
                          LEFT JOIN educational_work_hours EWH ON EWH.plan_work_id = EW.id
                          WHERE TP.id = :planeId
                          GROUP BY EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place
                          ORDER BY EW.order_place)";

    Arguments args;
    args.insert(":planeId", planeId);

    auto query = Database::get()->selectQuery(queryString, args);
    setQuery(query);
}

void ModelEducationWork::deleteWork(int id)
{

}

QHash<int, ModelEducationWork::Hour> ModelEducationWork::hours(int row) const
{
    QHash<int, ModelEducationWork::Hour> hours;
    QString hoursString = data(index(row, (int)Fields::Hours)).toString();
    QStringList splittedHours = hoursString.split(";", Qt::SkipEmptyParts);
    for(const QString &hourRow : qAsConst(splittedHours)){
        QStringList h = hourRow.split(",");
        int id = h.at((int)HourFields::HourId).toInt();
        int week = h.at((int)HourFields::HourWeek).toInt();
        HourType type = (HourType)h.at((int)HourFields::HourType).toInt();
        int value = h.at((int)HourFields::HourValue).toInt();

        auto current = hours.value(week);
        current.week = week;
        if(type == HourType::Plane){
            current.planId = id;
            current.planValue = value;
        } else {
            current.factId = id;
            current.factValue = value;
        }
        hours.insert(week, current);
    }

    return hours;
}

void ModelEducationWork::updateValues(Hour hour)
{
    QString queryString = R"()";

    Arguments args;
    // args.insert(":planeId", planeId);

    // auto query = Database::get()->selectQuery(queryString, args);
}
