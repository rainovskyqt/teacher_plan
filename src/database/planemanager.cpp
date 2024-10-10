#include "database.h"
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
