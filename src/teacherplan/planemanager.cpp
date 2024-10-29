#include "database/database.h"
#include "planemanager.h"

#include <QVariant>

Q_GLOBAL_STATIC(PlaneManager, globalInst)

PlaneManager::PlaneManager(QObject *parent)
    : QObject{parent}
{}

PlaneManager *PlaneManager::get()
{
    return globalInst();
}

int PlaneManager::planByStaff(int staffId)
{
    auto base = Database::get();

    QString queryString = R"(SELECT id
                             FROM teacher_plan
                             WHERE staff_id = :staffId)";

    Arguments args;
    args.insert(":staffId", staffId);

    auto answer = base->selectQuery(queryString, args);
    if(answer.next()){
        return answer.value("id").toInt();
    }
    return 0;
}

TeacherPlan *PlaneManager::staffPlan(int staff)
{
    auto base = Database::get();

    QString queryString = R"(SELECT `id`, `staff_id`, `year_id`, `rate`, `status_id`, `approved_user_id`, `approved_date`,
                             `department_boss_sign_id`, `protocol_number`, `protocol_date`,`comments`
                             FROM teacher_plan
                             WHERE staff_id = :staffId)";

    Arguments args;
    args.insert(":staffId", staff);


    auto answer = base->selectQuery(queryString, args);

    TeacherPlan *plan = new TeacherPlan(this);

    if(answer.next()){
        plan->setId(answer.value("id").toInt());
        plan->setStaffId(answer.value("staff_id").toInt());
        plan->setYearId(answer.value("year_id").toInt());
        plan->setRate(answer.value("rate").toDouble());
        plan->setStatusId(answer.value("status_id").toInt());
        plan->setApprovedUserId(answer.value("approved_user_id").toInt());
        plan->setApprovedDate(answer.value("approved_date").toDate());
        plan->setDepartmentBossSignId(answer.value("department_boss_sign_id").toInt());
        plan->setProtocolNumber(answer.value("protocol_number").toString());
        plan->setProtocolDate(answer.value("teacher_plan").toDate());
        plan->setComments(answer.value("comments").toString());
    }

    return plan;
}

void PlaneManager::savePlan(TeacherPlan *plan)
{
    Arguments args;
    args.insert(":base_id", plan->id());
    args.insert(":staff_id", plan->staffId());
    args.insert(":year_id", plan->yearId());
    args.insert(":status_id", plan->statusId());
    args.insert(":rate", plan->rate());

    QString update = "UPDATE teacher_plan SET status_id = :status_id, rate = :rate WHERE id = :base_id";
    QString insert = "INSERT INTO teacher_plan(staff_id, year_id, status_id, rate) "
                     "VALUES(:staff_id, :year_id, :status_id, :rate) ";

    if(plan->id()){
        Database::get()->updateDeleteQuery(update, args);
    } else {
        int id = Database::get()->insertQuery(insert, args);
        plan->setId(id);
    }
}
