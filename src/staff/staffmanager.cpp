#include "staffmanager.h"

#include <database/database.h>
#include <database/staff.h>

#include <QVariant>


Q_GLOBAL_STATIC(StaffManager, globalInst)

StaffManager::StaffManager(QObject *parent)
    : QObject{parent}
{}

StaffManager *StaffManager::get()
{
    return globalInst;
}

void StaffManager::saveStaff(int userId, Staff staff)
{
    QMap<QString, QVariant> args;
    args.insert(":user_id", userId);
    args.insert(":dep_id", staff.departmentId());
    args.insert(":post_id", staff.postId());
    args.insert(":year_id", staff.year());
    args.insert(":staff_id", staff.id());
    args.insert(":rate", staff.rate());

    QString update = "UPDATE staff SET post_id = :post_id, rate = :rate WHERE id = :staff_id";

    QString insert = "INSERT INTO staff(user_id, department_id, post_id, year, rate) "
                     "VALUES(:user_id, :dep_id, :post_id, :year_id, :rate) ";

    if(staff.id()){
        Database::get()->updateDeleteQuery(update, args);
    } else {
        Database::get()->insertQuery(insert, args);
    }
}

void StaffManager::deleteStaff(int staffId)
{

}

Staff *StaffManager::getStaff(int staffId)
{
    QMap<QString, QVariant> args;
    args.insert(":id", staffId);

    QString select = "SELECT id, user_id, department_id, post_id, rate, `year` "
                     "FROM staff "
                     "WHERE id = :id";

    auto answer = Database::get()->selectQuery(select, args);
    if(answer.next()){
        Staff* s = new Staff(answer.value("id").toInt(),
                             answer.value("user_id").toInt(),
                             answer.value("department_id").toInt(),
                             answer.value("post_id").toInt(),
                             answer.value("rate").toDouble(),
                             answer.value("year").toInt());
        return s;
    }

    return nullptr;
}

