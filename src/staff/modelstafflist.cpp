#include "modelstafflist.h"

#include <QDebug>
#include <QSqlQuery>

ModelStaffList::ModelStaffList(QObject *parent) : QSqlQueryModel(parent)
{}

void ModelStaffList::loadByDepartment(int year, int departmentId)
{
    QString where = "WHERE S.year = :year ";
    if(departmentId)
        where += "AND S.department_id = :department_id ";

    Arguments args;
    args.insert(":year", year);
    args.insert(":department_id", departmentId);
    loadStaff(where, args);
}

void ModelStaffList::loadByUserId(int userId)
{
    QString where = " WHERE U.id = :userId ";
    Arguments args;
    args.insert(":userId", userId);
    loadStaff(where, args);
}

QVector<QPair<int, QString> > ModelStaffList::departments(int yearId)
{
    QVector<QPair<int, QString>> deps;
    for (int row = 0; row < rowCount(); ++row) {
        if(data(index(row, YearId)).toInt() != yearId)
            continue;

        QString dName = data(index(row, DepartmentName)).toString();
        if (!exists(deps, dName)) {
            int sId = data(index(row, DepartmentId)).toInt();
            deps.append(qMakePair(sId, dName));
        }
    }
    return deps;
}

QVector<QPair<int, QString>> ModelStaffList::posts(int depId)
{
    QVector<QPair<int, QString>> post;
    for (int row = 0; row < rowCount(); ++row) {
        if(data(index(row, DepartmentId)).toInt() != depId)
            continue;

        QString pName = data(index(row, PostName)).toString();
        int sId = data(index(row, StaffId)).toInt();         //Добавляем именно id преподавателя как staff
        post.append(qMakePair(sId, pName));
    }

    return post;
}

void ModelStaffList::loadStaff(QString where, Arguments args)
{
    QString queryString = QString("SELECT U.id AS u_id, U.surname AS u_sname, U.`name` AS u_name, U.middle_name AS u_mname, "
                                  "S.id AS s_id, S.department_id AS d_id, D.`name` AS d_name, S.post_id AS p_id, P.`name` AS p_name, S.main AS s_main,"
                                  "S.`year` AS y_id, TP.rate "
                                  "FROM `user` U "
                                  "INNER JOIN staff S ON S.user_id = U.id "
                                  "INNER JOIN department D ON S.department_id = D.id "
                                  "INNER JOIN post P ON S.post_id = P.id "
                                  "LEFT JOIN teacher_plan TP ON TP.staff_id = S.id "
                                  "%1 "
                                  "ORDER BY U.surname, U.`name`, TP.rate DESC").arg(where);

    auto query = Database::get()->selectQuery(queryString, args);

    setQuery(query);
}

bool ModelStaffList::exists(const QVector<QPair<int, QString> > &list, const QString &name)
{
    for(const auto &v : list){
        if(v.second == name)
            return true;
    }
    return false;
}
