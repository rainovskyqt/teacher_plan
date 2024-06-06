#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QNetworkReply>
#include <QSqlError>

#include <login/user.h>

Q_GLOBAL_STATIC(Database, globalInst)

Database *Database::get()
{
    return globalInst();
}

void Database::init(QString host, int port)
{
    QSqlDatabase base = QSqlDatabase::addDatabase("QMYSQL");
    base.setHostName(host);
    base.setPort(port);
    base.setDatabaseName("ordo_dev");
    base.setUserName("ordo");
    base.setPassword("ordo7532159");
}

int Database::addUser(User *user)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString queryString = "INSERT INTO user(login, password, surname, name, middle_name, rang_id) "
                          "VALUES (:login, :password, :surname, :name, :middle_name, :rang_id)";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":login", user->userData()->login());
    query.bindValue(":password", encodePassword(user->userData()->password()));
    query.bindValue(":surname", user->userData()->surname());
    query.bindValue(":name", user->userData()->name());
    query.bindValue(":middle_name", user->userData()->middle_name());
    if(user->userData()->rangId())
        query.bindValue(":rang_id", user->userData()->rangId());
    query.exec();

    query.next();
    int id = query.lastInsertId().toInt();
    addPosts(user->posts(), id);

    base.close();
    return id;
}

void Database::addPosts(QMultiMap<int, int> posts, int userId)
{
    for(auto post = posts.begin(); post != posts.end(); ++post){
        addPost(userId, post.key(), post.value());
    }
}

int Database::addPost(int userId, int departmentId, int postId)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString queryString = "INSERT INTO staff(user_id, department_id, post_id) "
                          "VALUES (:user_id, :department_id, :post_id)";

    QSqlQuery query;
    query.prepare(queryString);

    query.bindValue(":user_id", userId);
    query.bindValue(":department_id", departmentId);
    query.bindValue(":post_id", postId);
    query.exec();

    qDebug() << query.lastError().text();

    base.close();
    return query.lastInsertId().toInt();
}

QList<Dictionary> Database::getDictionary(DictName name)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString tableName;

    switch(name){
    case Department:
        tableName = "department";
        break;
    case Post:
        tableName = "post";
        break;
    case Rang:
        tableName = "rang";
        break;
    }

    QString queryString = QString("SELECT id, name FROM %1").arg(tableName);
    QSqlQuery query;
    query.prepare(queryString);
    query.exec();

    QList<Dictionary> list;
    while(query.next()){
        list.append(Dictionary(query.value("id").toInt(), query.value("name").toString()));
    }

    base.close();

    return list;
}

QList<StudyYear> Database::getYears()
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString queryString = "SELECT id, begin_year, end_year "
                          "FROM educational_years ";

    QSqlQuery query;
    query.prepare(queryString);
    query.exec();

    QList<StudyYear> list;
    while(query.next()){
        list.append(StudyYear(query.value("begin_year").toString(),
                              query.value("end_year").toString(),
                              query.value("id").toInt()));
    }

    return list;
}

User *Database::login(QString login, QString password)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString queryString = "SELECT U.id AS 'uid', U.login, U.password, U.surname, U.name, U.middle_name, U.rang_id, R.name AS 'rname', "
                          "S.department_id, S.post_id "
                          "FROM user U "
                          "LEFT JOIN `rang` R ON U.rang_id = R.id "
                          "INNER JOIN `staff` S ON S.user_id = U.id "
                          "WHERE `login` = :login AND `password` = :password";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":login", login);
    query.bindValue(":password", encodePassword(password));
    query.exec();

    qDebug() << query.lastError().text();

    User *user = new User();
    while(query.next()){
        user->setBaseId(query.value("uid").toInt());
        user->userData()->setData(
            query.value("login").toString(),
            query.value("surname").toString(),
            query.value("name").toString(),
            query.value("middle_name").toString(),
            query.value("rname").toString(),
            query.value("rang_id").toInt()
            );
        user->addPost(query.value("department_id").toInt(), query.value("post_id").toInt());
    }

    return user;
}

QString Database::encodePassword(QString password)
{
    return QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
}

TeacherPlan * Database::requestPlan(int userId, int yearId, int departmentId, int postId)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QString queryString = "SELECT P.id AS pid, P.status_id, P.approved_user_id, P.approved_date, P.rate, P.protocol_number, "
                          "P.protocol_date, H.id, HT.name AS 'hmame', H.work_type_id, H.first_semester, H.second_semester, H.order_place "
                          "FROM teacher_plan P "
                          "LEFT JOIN teacher_plan_total_hours H ON H.teacher_plan_id = P.id "
                          "LEFT JOIN teacher_plan_works_type HT ON H.work_type_id = HT.id "
                          "WHERE user_id = :user_id AND department_id = :department_id AND post_id = :post_id AND year_id = :year_id";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":user_id", userId);
    query.bindValue(":year_id", yearId);
    query.bindValue(":department_id", departmentId);
    query.bindValue(":post_id", postId);
    query.exec();

    qDebug() << query.lastError().text();

    TeacherPlan *plan = new TeacherPlan();
    plan->setUserId(userId);
    plan->setYearId(yearId);
    plan->setDepartmentId(departmentId);
    plan->setPostId(postId);

    while(query.next()){
        plan->setBaseId(query.value("pid").toInt());
        plan->setStatusId(query.value("status_id").toInt());
        plan->setApproveUserId(query.value("approved_user_id").toInt());
        plan->setApproveDate(query.value("approved_date").toDate());
        plan->setRate(query.value("approved_user_id").toDouble());
        plan->setProtocolNumber(query.value("protocol_number").toString());
        plan->setProtocolDate(query.value("protocol_date").toDate());
        plan->addHour(query.value("order_place").toInt(),
                      new PlanTime(query.value("work_type_id").toInt(),
                                   query.value("hmame").toString(),
                                   query.value("first_semester").toInt(),
                                   query.value("second_semester").toInt(),
                                   query.value("second_semester").toInt(),
                                   query.value("order_place").toInt()
                                   ));
    }

    return plan;
}

void Database::updateTeacherPlan(TeacherPlan *plan)
{
    //     QString point = m_serverUrl.url() + "/academy/pplan/plan";

    //     QVariantMap planeMap;
    //     planeMap.insert("base_id", plan->baseId());
    //     planeMap.insert("user_id", plan->userId());
    //     planeMap.insert("department_id", plan->departmentId());
    //     planeMap.insert("post_id", plan->postId());
    //     planeMap.insert("year_id", plan->yearId());
    //     planeMap.insert("status_id", plan->statusId());
    //     if(plan->approveUser()){
    //         planeMap.insert("approved_user_id", plan->approveUser()->baseId());
    //         planeMap.insert("approved_date", plan->approveDate().toString("yyyy-MM-dd"));
    //     }
    //     planeMap.insert("rate", plan->rate());
    //     if(plan->protocolDate().isValid()){
    //         planeMap.insert("protocol_number", plan->protocolNumber());
    //         planeMap.insert("protocol_date", plan->protocolDate().toString("yyyy-MM-dd"));
    //     }
    //     QJsonArray hours;
    //     auto planeHours = plan->hours();
    //     for (auto hour = planeHours.begin(); hour != planeHours.end(); ++hour) {
    //         QVariantMap hourMap;
    //         hourMap.insert("base_id", hour.value()->baseId());
    //         hourMap.insert("plan_id", plan->baseId());
    //         hourMap.insert("work_type_id", hour.value()->workType());
    //         hourMap.insert("first_semester", hour.value()->semesterHours(PlanTime::FirstSemester));
    //         hourMap.insert("second_semester", hour.value()->semesterHours(PlanTime::SecondSemestr));
    //         hourMap.insert("name", hour.value()->name());
    //         hourMap.insert("order_place", hour.key());
    //         hours.append(QJsonValue(QJsonObject::fromVariantMap(hourMap)));
    //     }
    //     planeMap.insert("hours", hours);

    //     inputToServer(point, QJsonDocument::fromVariant(planeMap), true, PlanId);
}

void Database::setHeaders(QNetworkRequest &request, Marks mark)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer " + m_token).toLatin1());
}

Database::Database(){}
