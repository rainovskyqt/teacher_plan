#ifndef MODELSTAFFLIST_H
#define MODELSTAFFLIST_H

#include <QSqlQueryModel>
#include <database/database.h>


class ModelStaffList : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit ModelStaffList(QObject *parent = nullptr);

    enum Fields{
        UserId,
        UserSurname,
        UserName,
        UserMiddleName,
        StaffId,
        DepartmentId,
        DepartmentName,
        PostId,
        PostName,
        StaffMain,
        YearId
    };

    void loadByDepartment(int year, int departmentId);
    void loadByUserId(int userId);

    QMap<int, QString> departments(int yearId);
    QMap<int, QString> posts(int depId);

private:
    void loadStaff(QString where, Arguments arg = {});
};

#endif // MODELSTAFFLIST_H
