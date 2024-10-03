#include "modelstafflist.h"

#include <QDebug>
#include <QSqlQuery>

#include <database/database.h>


ModelStaffList::ModelStaffList() {}

void ModelStaffList::loadStaff(int facultyId)
{
    setHorizontalHeaderLabels(QStringList() << "Факультет");

    QString dep = "";
    Arguments arg;

    if(facultyId){
        dep = "WHERE S.department_id = :department_id";
        arg.insert(":department_id", facultyId);
    }

    QString queryString = QString("SELECT D.id AS d_id, D.`name` AS d_name, U.id AS u_id, U.surname AS u_sname, U.`name` AS u_name, "
                                  "U.middle_name AS u_mname "
                                  "FROM department D "
                                  "INNER JOIN staff S ON S.department_id = D.id "
                                  "INNER JOIN `user` U ON U.id = S.user_id "
                                  "%1 "
                                  "ORDER BY d_name, u_sname").arg(dep);

    auto query = Database::get()->executeQuery(queryString, arg);

    QMap<QString, QStringList> uniqueStaffMap;
    QMap<QString, int> userIds;
    QMap<QString, int> deprIds;

    while (query->next()) {
        QString dName = query->value("d_name").toString();
        int dId = query->value("d_id").toInt();
        QString uName = QString("%1 %2 %3").arg(query->value("u_sname").toString(),
                                                query->value("u_name").toString(),
                                                query->value("u_mname").toString());
        deprIds.insert(dName, dId);

        // Добавление имени сотрудника в соответствующий отдел
        if (!uniqueStaffMap[dName].contains(uName)) {
            uniqueStaffMap[dName].append(uName); // Добавляем только уникальные имена
            userIds.insert(uName, query->value("u_id").toInt());
        }
    }

    // Заполнение модели уникальными именами
    for (auto it = uniqueStaffMap.constBegin(); it != uniqueStaffMap.constEnd(); ++it) {
        const QString& dName = it.key();
        const QStringList& staffNames = it.value();

        // Создание родительского элемента для отдела
        QStandardItem* parentItem = new QStandardItem(dName);
        parentItem->setData(deprIds.value(dName), Qt::UserRole);
        appendRow(parentItem);

        for (const QString& uName : staffNames) {
            // Создание дочернего элемента для уникального имени сотрудника
            QStandardItem* childItem = new QStandardItem(uName);
            childItem->setData(userIds.value(uName), Qt::UserRole);
            parentItem->appendRow(childItem);
        }
    }
    delete query;
}

QModelIndex ModelStaffList::getUserIndex(int userId, int departmentId)
{
    qDebug() << "userId:" <<userId << "  departmentId: " << departmentId;
    auto dep = getItem(invisibleRootItem(), departmentId);
    if(!dep)
        return QModelIndex();

    auto user = getItem(dep, userId);
    if(!user)
        return QModelIndex();

    return indexFromItem(user);
}

QStandardItem *ModelStaffList::getItem(QStandardItem *parent, int id)
{
    for (int row = 0; row < parent->rowCount(); ++row) {
        QStandardItem* item = parent->child(row);
        if (item->data(Qt::UserRole).toInt() == id) {
            return item;
        }
    }
    return nullptr;
}
