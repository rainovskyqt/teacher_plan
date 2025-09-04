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

    QVector<QPair<int, QString>> departments(int yearId);
    QVector<QPair<int, QString>> posts(int depId);

    void departmentList(int year, int departmentId);

private:
    void loadStaff(QString where, Arguments arg = {});
    void loadDepartmentList(int yearId, int depId);
    bool exists(const QVector<QPair<int, QString>> &list, const QString &name);
};

#endif // MODELSTAFFLIST_H
