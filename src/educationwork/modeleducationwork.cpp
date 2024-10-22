#include "modeleducationwork.h"

#include <QDebug>

#include "database/database.h"
#include "educationwork.h"

ModelEducationWork::ModelEducationWork(QObject *parent)
    : QObject{parent}
{}

QList<EducationWork *> ModelEducationWork::loadData(int planeId)
{
    QString queryString = R"(SELECT EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place,
                          GROUP_CONCAT(CONCAT(EH.id,',', EH.`week`,',', EH.`plane`,',', EH.`fact`) SEPARATOR ';') AS hours
                          FROM educational_work EW
                          INNER JOIN teacher_plan TP ON TP.id = EW.teacher_plan_id
                          LEFT JOIN educational_hours EH ON EH.plan_work_id = EW.id
                          WHERE TP.id = :planeId
                          GROUP BY EW.id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place
                          ORDER BY EW.order_place)";

    Arguments args;
    args.insert(":planeId", planeId);

    auto query = Database::get()->selectQuery(queryString, args);

    QList<EducationWork*> list;
    while(query.next()){
        EducationWork *work = new EducationWork(this);
        work->setId(query.value("id").toInt());
        work->setDisciplineId(query.value("discipline_id").toInt());
        work->setCourseId(query.value("course_id").toInt());
        work->setWorkFormId(query.value("work_form_id").toInt());
        work->setGroupCount(query.value("group_count").toInt());
        work->setComments(query.value("comments").toString());
        work->setOrderPalce(query.value("order_place").toInt());
        work->setHours(query.value("hours").toString());
        list.append(work);
    }
    return list;
}

void ModelEducationWork::deleteWork(int id)
{

}
