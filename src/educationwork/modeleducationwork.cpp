#include "modeleducationwork.h"

#include <QDebug>

#include "database/database.h"
#include "educationwork.h"

ModelEducationWork::ModelEducationWork(QObject *parent)
    : QObject{parent}
{}

QList<EducationWork *> ModelEducationWork::loadData(int planeId)
{
    QString queryString = R"(SELECT EW.id, EW.teacher_plan_id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments, EW.order_place,
                          GROUP_CONCAT(CONCAT(EH.id,',', EH.`week`,',', EH.`plane`,',', EH.`fact`) SEPARATOR ';') AS hours
                          FROM educational_work EW
                          INNER JOIN teacher_plan TP ON TP.id = EW.teacher_plan_id
                          LEFT JOIN educational_hours EH ON EH.plan_work_id = EW.id
                          WHERE TP.id = :planeId
                          GROUP BY EW.id, EW.teacher_plan_id, EW.discipline_id, EW.course_id, EW.work_form_id, EW.group_count, EW.comments,
                          EW.order_place
                          ORDER BY EW.order_place)";

    Arguments args;
    args.insert(":planeId", planeId);

    auto query = Database::get()->selectQuery(queryString, args);

    QList<EducationWork*> list;
    while(query.next()){
        EducationWork *work = new EducationWork(this);
        work->setId(query.value("id").toInt());
        work->setTeacherPlanId(query.value("teacher_plan_id").toInt());
        work->setDisciplineId(query.value("discipline_id").toInt());
        work->setCourseId(query.value("course_id").toInt());
        work->setWorkFormId(query.value("work_form_id").toInt());
        work->setGroupCount(query.value("group_count").toInt());
        work->setComments(query.value("comments").toString());
        work->setOrderPlace(query.value("order_place").toInt());
        work->setHours(query.value("hours").toString());
        list.append(work);
    }
    return list;
}

void ModelEducationWork::saveHours(EducationWork *w, int week)
{
    QString updateQuery = "UPDATE educational_hours SET plane = :plane, fact = :fact WHERE id = :id";
    QString insertQuery = "INSERT INTO educational_hours (plan_work_id, week, plane, fact) "
                          "VALUES (:plan_work_id, :week, :plane, :fact)";
    QString deleteQuery = "DELETE FROM educational_hours WHERE id = :id";

    int plane = w->hours().value(week)->plan();
    int fact = w->hours().value(week)->fact();
    int id = w->hours().value(week)->id();

    Arguments args;
    args.insert(":plan_work_id", w->id());
    args.insert(":week", week);
    args.insert(":plane", plane);
    args.insert(":fact", fact);
    args.insert(":id", id);

    if(!plane && !fact){
        Database::get()->updateDeleteQuery(deleteQuery, args);
    } else if(!id){
        int newId = Database::get()->insertQuery(insertQuery, args);
        w->hours().value(week)->setId(newId);
    } else {
        Database::get()->updateDeleteQuery(updateQuery, args);
    }
}

void ModelEducationWork::deleteWork(int id)
{
    QString queryString = QString("DELETE FROM educational_work WHERE id = :id");
    Arguments args;
    args.insert(":id", id);
    Database::get()->updateDeleteQuery(queryString, args);
}

void ModelEducationWork::saveWork(EducationWork *w)
{
    Arguments args;
    args.insert(":id", w->id());
    args.insert(":teacher_plan_id", w->teacherPlanId());
    args.insert(":discipline_id", w->disciplineId());
    args.insert(":work_form_id", w->workFormId());
    args.insert(":course_id", w->courseId());
    args.insert(":group_count", w->groupCount());
    args.insert(":comments", w->comments());
    args.insert(":order_place", w->orderPlace());

    QString updateString = "UPDATE educational_work "
                           "SET discipline_id = :discipline_id, work_form_id = :work_form_id, course_id = :course_id, "
                           "group_count = :group_count, comments = :comments, order_place = :order_place "
                           "WHERE id = :id";

    QString insertString = "INSERT INTO educational_work(teacher_plan_id, discipline_id, work_form_id, course_id, "
                           "group_count, comments, order_place)"
                           "VALUES(:teacher_plan_id, :discipline_id, :work_form_id, :course_id,"
                           ":group_count, :comments, :order_place) ";
    if(w->id()){
        Database::get()->updateDeleteQuery(updateString, args);
    } else {
        int id =Database::get()->insertQuery(insertString, args);
        w->setId(id);
    }
}
