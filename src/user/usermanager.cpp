#include "usermanager.h"

#include "database/database.h"

#include <QVariant>

Q_GLOBAL_STATIC(UserManager, globalInst)

UserManager::UserManager(QObject *parent)
    : QObject{parent}
{}

UserManager *UserManager::get()
{
    return globalInst();
}

bool UserManager::login(const QString &login, const QString &password)
{
    auto base = Database::get();

    QString queryString = "SELECT id  "
                          "FROM user U "
                          "WHERE `login` = :login AND `password` = :password ";
    Arguments args;
    args.insert(":login", login);
    args.insert(":password", password);

    auto answer = base->selectQuery(queryString, args);

    if(answer.next()){
        int id = answer.value("id").toInt();
        auto user = getUser(id);
        if(user){
            setUser(user);
            return true;
        }
    }
    return false;
}

User *UserManager::getUser(int id)
{
    auto base = Database::get();

    QString queryString = "SELECT U.id AS 'uid', U.surname, U.name, U.middle_name, U.rang_id, R.name AS 'rname', "
                          "S.department_id, S.post_id, S.id AS staff_id, S.main AS main, D.name as d_name, P.name AS p_name, "
                          "SAR.rights AS rights, S.rate AS rate, S.year AS year "
                          "FROM user U "
                          "LEFT JOIN `rang` R ON U.rang_id = R.id "
                          "INNER JOIN `staff` S ON S.user_id = U.id "
                          "INNER JOIN `department` D ON D.id = S.department_id "
                          "INNER JOIN `post` P ON P.id = S.post_id "
                          "LEFT JOIN staff_access_rigth SAR ON SAR.staff_id = S.id "
                          "WHERE U.id = :id "
                          "ORDER BY main, staff_id";

    Arguments args;
    args.insert(":id", QVariant(id));

    auto answer = base->selectQuery(queryString, args);

    User *user = new User();

    while(answer.next()){
        user->setId(answer.value("uid").toInt());
        user->setSurname(answer.value("surname").toString());
        user->setName(answer.value("name").toString());
        user->setMiddleName(answer.value("middle_name").toString());
        user->addStaff(new Staff(answer.value("uid").toInt(),
                                 answer.value("staff_id").toInt(),
                                 answer.value("department_id").toInt(),
                                 answer.value("d_name").toString(),
                                 answer.value("post_id").toInt(),
                                 answer.value("p_name").toString(),
                                 answer.value("main").toBool(),
                                 answer.value("rate").toBool(),
                                 answer.value("year").toBool())
                       );
        user->addRights(answer.value("rights").toString());
    }
    return user;
}

QVector<QPair<int, QString>> UserManager::allUserList()
{
    auto base = Database::get();

    QString select = "SELECT id, CONCAT(surname, ' ', `name`, ' ', middle_name) AS full_name "
                     "FROM `user` "
                     "ORDER BY surname, `name`";
    QVector<QPair<int, QString>> list;

    auto answer = base->selectQuery(select);
    while (answer.next()) {
        list.append(qMakePair(answer.value("id").toInt(), answer.value("full_name").toString()));
    }
    return list;
}

User *UserManager::user() const
{
    return m_user;
}

bool UserManager::userStaff(int staff)
{
    const auto staffList = m_user->allStaff();
    for(const auto &s : staffList)
        if(s->id() == staff)
            return true;

    return false;
}

void UserManager::setUser(User *user)
{
    if(m_user)
        m_user->deleteLater();
    m_user = user;
}
