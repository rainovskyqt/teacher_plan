#include "usermanager.h"

#include "database/database.h"
#include "user.h"

#include <QVariant>

Q_GLOBAL_STATIC(UserManager, globalInst)

UserManager::UserManager(QObject *parent)
    : QObject{parent}
    ,m_user(new User)
{}

UserManager *UserManager::get()
{
    return globalInst();
}

bool UserManager::login(const QString &login, const QString &password)
{
    auto base = Database::get();

    QString queryString = "SELECT U.id AS 'uid', U.surname, U.name, U.middle_name, U.rang_id, R.name AS 'rname', "
                          "S.department_id, S.post_id, S.id AS staff_id, S.main AS main, D.name as d_name, P.name AS p_name, "
                          "SAR.rights AS rights "
                          "FROM user U "
                          "LEFT JOIN `rang` R ON U.rang_id = R.id "
                          "INNER JOIN `staff` S ON S.user_id = U.id "
                          "INNER JOIN `department` D ON D.id = S.department_id "
                          "INNER JOIN `post` P ON P.id = S.post_id "
                          "LEFT JOIN staff_access_rigth SAR ON SAR.staff_id = S.id "
                          "WHERE `login` = :login AND `password` = :password "
                          "ORDER BY main, staff_id";

    Database::Values vals;
    vals.insert(":login", QVariant(login));
    vals.insert(":password", QVariant(password));

    auto answer = base->executeQuery(queryString, vals);
    while(answer->next()){
        m_user->setId(answer->value("uid").toInt());
        m_user->setSurname(answer->value("surname").toString());
        m_user->setName(answer->value("name").toString());
        m_user->setMiddleName(answer->value("middle_name").toString());
        m_user->addStaff(new Staff(answer->value("staff_id").toInt(),
                                   answer->value("department_id").toInt(),
                                   answer->value("d_name").toString(),
                                   answer->value("post_id").toInt(),
                                   answer->value("p_name").toString(),
                                   answer->value("main").toBool())
                         );
        m_user->addRights(answer->value("rights").toString());
    }
    delete answer;
    return m_user->id();
}

User *UserManager::user()
{
    return m_user;
}
