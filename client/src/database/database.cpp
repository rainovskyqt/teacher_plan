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
#include "database/models/educationalwork.h"

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
    case Discipline:
        tableName = "discipline";
        break;
    case Group:
        tableName = "`group`";
        break;
    case WorkForm:
        tableName = "work_form";
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

QVector<EducationalWork*> Database::educationWork(int planId)
{
    QVector<EducationalWork*> works;

    QString queryString = "SELECT id, discipline_id, work_form_id, group_id, comments, order_place "
                          "FROM educational_work "
                          "WHERE teacher_plan_id = :teacher_plan_id "
                          "ORDER BY order_place";
    Values vals;
    vals.insert(":teacher_plan_id", planId);

    auto query = executeQuery(queryString, vals);
    while (query->next()) {
        auto work = new EducationalWork(planId);
        work->setBaseId(query->value("id").toInt());
        work->setDisciplineId(query->value("discipline_id").toInt());
        work->setWorkFormId(query->value("work_form_id").toInt());
        work->setGroupId(query->value("group_id").toInt());
        work->setComments(query->value("comments").toString());
        works.append(work);
    }

    return works;
}

void Database::saveWork(TeacherWork *work)
{
    TeacherWork::WorkType type = work->workType();
    switch (type) {
    case TeacherWork::Educational:
        saveEducationalWork(work);
        break;
    case TeacherWork::MethodicWork:
    case TeacherWork::SearchingWork:
    case TeacherWork::SportWork:
    case TeacherWork::OtherWork:
        saveGenericWork(work);
    }
}

void Database::deleteWork(TeacherWork *work)
{
    QString table;
    TeacherWork::WorkType type = work->workType();
    switch (type) {
    case TeacherWork::Educational:
        table = "educational_work";
        break;
    case TeacherWork::MethodicWork:
    case TeacherWork::SearchingWork:
    case TeacherWork::SportWork:
    case TeacherWork::OtherWork:
        table = "teacher_work";
    }
    QString queryString = QString("DELETE FROM %1 WHERE id = :id").arg(table);
    Values vals;
    vals.insert(":id", work->baseId());
    delete executeQuery(queryString, vals);
}

QList<EducationalHour *> Database::getEdcationalHours(int workId)
{
    QString queryString = "SELECT id, `month`, `week`, `value`, `type` FROM educational_work_hours "
                          "WHERE plan_work_id = :plan_work_id";
    Values vals;
    vals.insert(":plan_work_id", workId);
    auto query = executeQuery(queryString, vals);

    QList<EducationalHour *> hList;

    while (query->next()) {
        hList.append(
            new EducationalHour(
                query->value("id").toInt(),
                workId,
                query->value("month").toInt(),
                query->value("week").toInt(),
                query->value("value").toInt(),
                static_cast<EducationalHour::HourType>(query->value("type").toInt()))
            );
    }

    return hList;
}

int Database::saveEdcationalHour(EducationalHour *hour)
{
    Values vals;
    vals.insert(":id", hour->baseId());
    vals.insert(":month", hour->month());
    vals.insert(":week", hour->week());
    vals.insert(":value", hour->value());
    vals.insert(":type", hour->type());
    vals.insert(":plan_work_id", hour->planeWorkId());

    QString updateString = "UPDATE educational_work_hours "
                           "SET value = :value "
                           "WHERE id = :id";

    QString insertString = "INSERT INTO educational_work_hours(month, week, value, type, plan_work_id)"
                           "VALUES(:month, :week, :value, :type, :plan_work_id) ";
    if(hour->baseId()){
        delete executeQuery(updateString, vals);
        return hour->baseId();
    } else {
        auto answer = executeQuery(insertString, vals);
        answer->next();
        int id = answer->lastInsertId().toInt();
        delete answer;
        return id;
    }
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

    base.close();
    return query;
}

void Database::saveEducationalWork(TeacherWork *work)
{
    auto w = dynamic_cast<EducationalWork*>(work);
    Values vals;
    vals.insert(":id", w->baseId());
    vals.insert(":teacher_plan_id", w->planId());
    vals.insert(":discipline_id", w->disciplineId());
    vals.insert(":work_form_id", w->workFormId());
    vals.insert(":group_id", w->groupId());
    vals.insert(":comments", w->comments());
    vals.insert(":order_place", 0);

    QString updateString = "UPDATE educational_work "
                           "SET teacher_plan_id = :teacher_plan_id, discipline_id = :discipline_id, "
                           "work_form_id = :work_form_id, group_id = :group_id, "
                           "comments = :comments, order_place = :order_place "
                           "WHERE id = :id";

    QString insertString = "INSERT INTO educational_work(teacher_plan_id, discipline_id, work_form_id, group_id, "
                           "comments, order_place)"
                           "VALUES(:teacher_plan_id, :discipline_id, :work_form_id, :group_id,"
                           ":comments, :order_place) ";
    if(w->baseId()){
        delete executeQuery(updateString, vals);
    } else {
        auto answer = executeQuery(insertString, vals);
        answer->next();
        work->setBaseId(answer->lastInsertId().toInt());
    }
}

void Database::saveGenericWork(TeacherWork *work)
{

}

TeacherPlan * Database::requestPlan(int userId, int yearId, int departmentId, int postId)
{
    QString queryString = "SELECT P.id AS pid, P.status_id, P.approved_user_id, P.approved_date, P.rate, P.protocol_number, "
                          "P.protocol_date "
                          "FROM teacher_plan P "
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

    if(query->next()){
        plan->setBaseId(query->value("pid").toInt());
        plan->setStatusId(query->value("status_id").toInt());
        plan->setApproveUserId(query->value("approved_user_id").toInt());
        plan->setApproveDate(query->value("approved_date").toDate());
        plan->setRate(query->value("rate").toDouble());
        plan->setProtocolNumber(query->value("protocol_number").toString());
        plan->setProtocolDate(query->value("protocol_date").toDate());
    }

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
}


Database::Database(){}
