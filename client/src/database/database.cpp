#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>
#include <QSqlDatabase>
#include <QNetworkReply>
#include <QSqlError>

#include <login/user.h>

Q_GLOBAL_STATIC(Database, globalInst)

Database *Database::get()
{
    return globalInst();
}

bool Database::init(QString host, int port)
{
    QSqlDatabase base = QSqlDatabase::addDatabase("QMYSQL");
    base.setHostName(host);
    base.setPort(port);
    base.setDatabaseName("ordo_dev");
    base.setUserName("ordo");
    base.setPassword("ordo7532159");
    if(!base.open()){
        m_lastError = base.lastError().text();
        return false;
    }
    return true;
}

int Database::addUser(User *user)
{
    QString queryString = "INSERT INTO user(login, password, surname, name, middle_name, rang_id) "
                          "VALUES (:login, :password, :surname, :name, :middle_name, :rang_id)";

    Values vals;
    vals.insert(":login", user->userData()->login());
    vals.insert(":password", encodePassword(user->userData()->password()));
    vals.insert(":surname", user->userData()->surname());
    vals.insert(":name", user->userData()->name());
    vals.insert(":middle_name", user->userData()->middle_name());
    if(user->userData()->rangId())
        vals.insert(":rang_id", user->userData()->rangId());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    addPosts(user->posts(), id);

    delete query;
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

    QString queryString = "INSERT INTO staff(user_id, department_id, post_id) "
                          "VALUES (:user_id, :department_id, :post_id)";

    Values vals;
    vals.insert(":user_id", userId);
    vals.insert(":department_id", departmentId);
    vals.insert(":post_id", postId);

    auto query = executeQuery(queryString, vals);
    int id = query->lastInsertId().toInt();
    delete query;
    return id;
}

QList<Dictionary> Database::getDictionary(DictName name)
{
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

    auto query = executeQuery(queryString);

    QList<Dictionary> list;
    while(query->next()){
        list.append(Dictionary(query->value("id").toInt(), query->value("name").toString()));
    }

    delete query;
    return list;
}

QList<StudyYear> Database::getYears()
{
    QString queryString = "SELECT id, begin_year, end_year "
                          "FROM educational_years ";

    auto query = executeQuery(queryString);

    QList<StudyYear> list;
    while(query->next()){
        list.append(StudyYear(query->value("begin_year").toString(),
                              query->value("end_year").toString(),
                              query->value("id").toInt()));
    }

    delete query;
    return list;
}

User *Database::login(QString login, QString password)
{

    QString queryString = "SELECT U.id AS 'uid', U.login, U.password, U.surname, U.name, U.middle_name, U.rang_id, R.name AS 'rname', "
                          "S.department_id, S.post_id "
                          "FROM user U "
                          "LEFT JOIN `rang` R ON U.rang_id = R.id "
                          "INNER JOIN `staff` S ON S.user_id = U.id "
                          "WHERE `login` = :login AND `password` = :password";
    Values vals;
    vals.insert(":login", login);
    vals.insert(":password", encodePassword(password));

    auto query = executeQuery(queryString, vals);

    User *user = new User();
    while(query->next()){
        user->setBaseId(query->value("uid").toInt());
        user->userData()->setData(
            query->value("login").toString(),
            query->value("surname").toString(),
            query->value("name").toString(),
            query->value("middle_name").toString(),
            query->value("rname").toString(),
            query->value("rang_id").toInt()
            );
        user->addPost(query->value("department_id").toInt(), query->value("post_id").toInt());
    }
    delete query;
    return user;
}

QString Database::encodePassword(QString password)
{
    return QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
}

const QString &Database::lastError() const
{
    return m_lastError;
}

QSqlQuery* Database::executeQuery(QString queryString, Values vals)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QSqlQuery *query = new QSqlQuery(base);
    query->prepare(queryString);
    for(auto val = vals.begin(); val != vals.end(); ++val){
        query->bindValue(val.key(), val.value());
    }
    query->exec();

    if(query->lastError().isValid())
        qDebug() << query->lastError().text();

    return query;
}

Hours Database::getDefaultHours()
{
    QString queryString = "SELECT id, `name`, `order` FROM teacher_plan_works_type WHERE `enable` = 1 ORDER BY `order`";

    Hours hours;
    auto q = executeQuery(queryString);
    while (q->next()) {
        hours.insert(q->value("order").toInt(),
                     new PlanTime(q->value("id").toInt(), q->value("name").toString(), 0, 0, 0, q->value("order").toInt()));
    }
    return hours;
}

TeacherPlan * Database::requestPlan(int userId, int yearId, int departmentId, int postId)
{
    QString queryString = "SELECT P.id AS pid, P.status_id, P.approved_user_id, P.approved_date, P.rate, P.protocol_number, "
                          "P.protocol_date, H.id, HT.name AS 'hmame', H.work_type_id, H.first_semester, H.second_semester, H.order_place "
                          "FROM teacher_plan P "
                          "LEFT JOIN teacher_plan_total_hours H ON H.teacher_plan_id = P.id "
                          "LEFT JOIN teacher_plan_works_type HT ON H.work_type_id = HT.id "
                          "WHERE user_id = :user_id AND department_id = :department_id AND post_id = :post_id AND year_id = :year_id";

    Values vals;
    vals.insert(":user_id", userId);
    vals.insert(":year_id", yearId);
    vals.insert(":department_id", departmentId);
    vals.insert(":post_id", postId);

    auto query = executeQuery(queryString, vals);

    TeacherPlan *plan = new TeacherPlan();
    plan->setUserId(userId);
    plan->setYearId(yearId);
    plan->setDepartmentId(departmentId);
    plan->setPostId(postId);

    while(query->next()){
        plan->setBaseId(query->value("pid").toInt());
        plan->setStatusId(query->value("status_id").toInt());
        plan->setApproveUserId(query->value("approved_user_id").toInt());
        plan->setApproveDate(query->value("approved_date").toDate());
        plan->setRate(query->value("rate").toDouble());
        plan->setProtocolNumber(query->value("protocol_number").toString());
        plan->setProtocolDate(query->value("protocol_date").toDate());
        plan->addHour(query->value("order_place").toInt(),
                      new PlanTime(query->value("work_type_id").toInt(),
                                   query->value("hmame").toString(),
                                   query->value("first_semester").toInt(),
                                   query->value("second_semester").toInt(),
                                   query->value("second_semester").toInt(),
                                   query->value("order_place").toInt()
                                   ));
    }

    if(plan->hours().isEmpty())
        plan->setHours(getDefaultHours());

    return plan;
}

void Database::updateTeacherPlan(TeacherPlan *plan)
{
    Values vals;
    vals.insert(":base_id", plan->baseId());
    vals.insert(":user_id", plan->userId());
    vals.insert(":department_id", plan->departmentId());
    vals.insert(":post_id", plan->postId());
    vals.insert(":year_id", plan->yearId());
    vals.insert(":status_id", plan->statusId());
    vals.insert(":rate", plan->rate());

    QString queryString;
    if(plan->baseId()){
        queryString = "UPDATE teacher_plan SET status_id = :status_id, rate = :rate WHERE id = :base_id";
        delete executeQuery(queryString, vals);
    } else {
        queryString = "INSERT INTO teacher_plan(user_id, department_id, post_id, year_id, status_id, rate) "
                      "VALUES(:user_id, :department_id, :post_id, :year_id, :status_id, :rate) ";
        auto query = executeQuery(queryString, vals);
        query->next();
        plan->setBaseId(query->lastInsertId().toInt());
        delete query;
    }

    updateHours(plan->hours(), plan->baseId());
}

void Database::setHeaders(QNetworkRequest &request, Marks mark)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer " + m_token).toLatin1());
}

void Database::updateHours(Hours hours, int planId)
{
    QString updateString = "UPDATE teacher_plan_total_hours SET "
                          "first_semester = :first_semester, second_semester = :second_semester "
                          "WHERE id = :base_id";
    QString insertString = "INSERT INTO teacher_plan_total_hours(teacher_plan_id, work_type_id, first_semester, "
                           "second_semester, order_place) "
                           "VALUES (:teacher_plan_id, :work_type_id, :first_semester, "
                           ":second_semester, :order_place)";

    Values vals;
    for (auto hour = hours.begin(); hour != hours.end(); ++hour) {
        vals.insert(":base_id", hour.value()->baseId());
        vals.insert(":teacher_plan_id", planId);
        vals.insert(":work_type_id", hour.value()->workType());
        vals.insert(":first_semester", hour.value()->semesterHours(PlanTime::FirstSemester));
        vals.insert(":second_semester", hour.value()->semesterHours(PlanTime::SecondSemestr));
        vals.insert(":order_place", hour.key());
        if(hour.value()->baseId()){
            delete executeQuery(updateString, vals);
        } else {
            auto query = executeQuery(insertString, vals);
            query->next();
            hour.value()->setBaseId(query->lastInsertId().toInt());
            delete query;
        }
    }
}

Database::Database(){}
