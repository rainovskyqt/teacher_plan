#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

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
    base.setDatabaseName("corusant");
    base.setUserName("ordo");
    base.setPassword("ordo7532159");
    if(!base.open()){
        m_lastError = base.lastError().text();
        return false;
    }
    base.close();
    return true;
}

const QString &Database::lastError() const
{
    return m_lastError;
}

QSqlQuery Database::executeQuery(QString queryString, Arguments args)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QSqlQuery query(base);
    query.prepare(queryString);
    for(auto arg = args.begin(); arg != args.end(); ++arg){
        query.bindValue(arg.key(), arg.value());
    }
    query.exec();

    if(query.lastError().isValid()){
        m_lastError = query.lastError().text();
        qDebug() << m_lastError;
    }

    base.close();
    return query;
}

QSqlQuery Database::selectQuery(QString queryString, Arguments args)
{
    return executeQuery(queryString, args);
}

int Database::insertQuery(QString queryString, Arguments args)
{
    auto query = executeQuery(queryString, args);
    return query.lastInsertId().toInt();
}

void Database::updateDeleteQuery(QString queryString, Arguments args)
{
    executeQuery(queryString, args);
}


// int Database::addUser(User *user)
// {
//     QString queryString = "INSERT INTO user(login, password, surname, name, middle_name, rang_id) "
//                           "VALUES (:login, :password, :surname, :name, :middle_name, :rang_id)";

//     Values vals;
//     vals.insert(":login", user->userData()->login());
//     vals.insert(":password", encodePassword(user->userData()->password()));
//     vals.insert(":surname", user->userData()->surname());
//     vals.insert(":name", user->userData()->name());
//     vals.insert(":middle_name", user->userData()->middle_name());
//     if(user->userData()->rangId())
//         vals.insert(":rang_id", user->userData()->rangId());

//     auto query = executeQuery(queryString, vals);
//     query->next();

//     int id = query->lastInsertId().toInt();
//     addPosts(user->posts(), id);

//     delete query;
//     return id;
// }

// void Database::addPosts(QList<UserPost> posts, int userId)
// {
//     foreach(auto p, posts){
//         addPost(p, userId);
//     }
// }

// int Database::addPost(UserPost post, int userId)
// {

//     QString queryString = "INSERT INTO staff(user_id, department_id, post_id, main) "
//                           "VALUES (:user_id, :department_id, :post_id, :main)";

//     Values vals;
//     vals.insert(":user_id", userId);
//     vals.insert(":department_id", post.departmentId);
//     vals.insert(":post_id", post.postId);
//     vals.insert(":main", post.main ? 1 : 0);


//     auto query = executeQuery(queryString, vals);
//     int id = query->lastInsertId().toInt();
//     delete query;
//     return id;
// }

// QVector<Dictionary> Database::getDictionary(DictName name)
// {
//     QString tableName;
//     QString order = "name";

//     switch(name){
//     case Department:
//         tableName = "department";
//         break;
//     case Post:
//         tableName = "post";
//         break;
//     case Rang:
//         tableName = "rang";
//         break;
//     case Discipline:
//         tableName = "discipline";
//         break;
//     case Course:
//         tableName = "`course`";
//         order.prepend("course, ");
//         break;
//     case WorkForm:
//         tableName = "educational_work_form";
//         order = "order_place";
//         break;
//     }

//     QString queryString = QString("SELECT id, name FROM %1 ORDER BY %2").arg(tableName, order);

//     auto query = executeQuery(queryString);

//     QVector<Dictionary> list;
//     while(query->next()){
//         list.append(Dictionary(query->value("id").toInt(), query->value("name").toString()));
//     }

//     delete query;
//     return list;
// }

// QList<StudyYear> Database::getYears()
// {
//     QString queryString = "SELECT id, begin_year, end_year "
//                           "FROM educational_years ";

//     auto query = executeQuery(queryString);

//     QList<StudyYear> list;
//     while(query->next()){
//         list.append(StudyYear(query->value("begin_year").toString(),
//                               query->value("end_year").toString(),
//                               query->value("id").toInt()));
//     }

//     delete query;
//     return list;
// }


// QVector<EducationalWork*> Database::educationWork(int planId)
// {
//     QVector<EducationalWork*> works;

//     QString queryString = "SELECT id, discipline_id, work_form_id, course_id, group_count, comments, order_place "
//                           "FROM educational_work "
//                           "WHERE teacher_plan_id = :teacher_plan_id "
//                           "ORDER BY order_place";
//     Values vals;
//     vals.insert(":teacher_plan_id", planId);

//     auto query = executeQuery(queryString, vals);
//     while (query->next()) {
//         auto work = new EducationalWork(planId);
//         work->setBaseId(query->value("id").toInt());
//         work->setDisciplineId(query->value("discipline_id").toInt());
//         work->setWorkFormId(query->value("work_form_id").toInt());
//         work->setCourseId(query->value("course_id").toInt());
//         work->setGroupCount(query->value("group_count").toInt());
//         work->setComments(query->value("comments").toString());
//         work->setOrderPlace(query->value("order_place").toInt());
//         works.append(work);
//     }
//     delete query;
//     return works;
// }

// QVector<GenericWork *> Database::genericWork(int planId, WorkType type)
// {
//     QVector<GenericWork*> works;

//     QString queryString = "SELECT W.id, work_form_id, semester, complite, order_place, plan_hours, fact_hours "
//                           "FROM generic_work W "
//                           "INNER JOIN generic_work_form F ON W.work_form_id = F.id "
//                           "WHERE W.teacher_plan_id = :teacher_plan_id AND F.work_type = :work_type "
//                           "ORDER BY semester, order_place";
//     Values vals;
//     vals.insert(":teacher_plan_id", planId);
//     vals.insert(":work_type", static_cast<int>(type));

//     auto query = executeQuery(queryString, vals);
//     while (query->next()) {
//         auto work = new GenericWork(type, planId);
//         work->setBaseId(query->value("id").toInt());
//         work->setWorkFormId(query->value("work_form_id").toInt());
//         work->setSemester(query->value("semester").toInt());
//         work->setComplite(query->value("complite").toString());
//         work->setOrderPlace(query->value("order_place").toInt());
//         work->setPlanHours(query->value("plan_hours").toInt());
//         work->setFactHours(query->value("fact_hours").toInt());
//         works.append(work);
//     }
//     delete query;
//     return works;
// }

// int Database::saveWork(TeacherWork *work)
// {
//     WorkType type = work->workType();
//     switch (type) {
//     case Educational:
//         return saveEducationalWork(work);
//     case MethodicWork:
//     case ResearchingWork:
//     case SportWork:
//     case OtherWork:
//     default:
//         return saveGenericWork(work);
//     }
// }

// void Database::deleteWork(TeacherWork *work)
// {
//     QString table;
//     WorkType type = work->workType();
//     switch (type) {
//     case Educational:
//         table = "educational_work";
//         break;
//     case MethodicWork:
//     case ResearchingWork:
//     case SportWork:
//     case OtherWork:
//         table = "generic_work";
//     }
//     QString queryString = QString("DELETE FROM %1 WHERE id = :id").arg(table);
//     Values vals;
//     vals.insert(":id", work->baseId());
//     delete executeQuery(queryString, vals);
// }

// QList<EducationalHour *> Database::getEdcationalHours(int workId)
// {
//     QString queryString = "SELECT id, `week`, `value`, `type` FROM educational_work_hours "
//                           "WHERE plan_work_id = :plan_work_id";
//     Values vals;
//     vals.insert(":plan_work_id", workId);
//     auto query = executeQuery(queryString, vals);

//     QList<EducationalHour *> hList;

//     while (query->next()) {
//         hList.append(
//             new EducationalHour(
//                 query->value("id").toInt(),
//                 workId,
//                 query->value("week").toInt(),
//                 query->value("value").toInt(),
//                 static_cast<EducationalHour::HourType>(query->value("type").toInt()))
//             );
//     }
//     delete query;
//     return hList;
// }

// int Database::saveEdcationalHour(EducationalHour *hour)
// {
//     Values vals;
//     vals.insert(":id", hour->baseId());
//     vals.insert(":week", hour->week());
//     vals.insert(":value", hour->value());
//     vals.insert(":type", hour->type());
//     vals.insert(":plan_work_id", hour->planeWorkId());

//     QString updateString = "UPDATE educational_work_hours "
//                            "SET value = :value "
//                            "WHERE id = :id";

//     QString insertString = "INSERT INTO educational_work_hours(week, value, type, plan_work_id)"
//                            "VALUES(:week, :value, :type, :plan_work_id) ";
//     if(hour->baseId()){
//         delete executeQuery(updateString, vals);
//         return hour->baseId();
//     } else {
//         auto answer = executeQuery(insertString, vals);
//         answer->next();
//         int id = answer->lastInsertId().toInt();
//         delete answer;
//         return id;
//     }
// }

// QList<GenericWorkForm*> Database::getWorks(WorkType type)
// {
//     QString queryString = "SELECT id, chapter, `name`, max_year_count, max_unit_count "
//                           "FROM generic_work_form "
//                           "WHERE work_type = :type";
//     Values vals;
//     vals.insert(":type", static_cast<int>(type));
//     auto query = executeQuery(queryString, vals);

//     QList<GenericWorkForm *> wList;

//     while (query->next()) {
//         wList.append(new GenericWorkForm(
//             query->value("id").toInt(),
//             query->value("chapter").toString(),
//             query->value("name").toString(),
//             query->value("max_year_count").toInt(),
//             query->value("max_unit_count").toInt()
//             ));
//     }
//     delete query;
//     return wList;
// }

// QSqlQuery* Database::executeQuery(QString queryString, Values vals)
// {
//     auto base = QSqlDatabase::database();
//     if(!base.open())
//         base.open();

//     QSqlQuery *query = new QSqlQuery(base);
//     query->prepare(queryString);
//     for(auto val = vals.begin(); val != vals.end(); ++val){
//         query->bindValue(val.key(), val.value());
//     }
//     query->exec();

//     if(query->lastError().isValid())
//         qDebug() << query->lastError().text();

//     base.close();
//     return query;
// }

// int Database::saveEducationalWork(TeacherWork *work)
// {
//     auto w = dynamic_cast<EducationalWork*>(work);
//     Values vals;
//     vals.insert(":id", w->baseId());
//     vals.insert(":teacher_plan_id", w->planId());
//     vals.insert(":discipline_id", w->disciplineId());
//     vals.insert(":work_form_id", w->workFormId());
//     vals.insert(":course_id", w->courseId());
//     vals.insert(":group_count", w->groupCount());
//     vals.insert(":comments", w->comments());
//     vals.insert(":order_place", w->orderPlace());

//     QString updateString = "UPDATE educational_work "
//                            "SET teacher_plan_id = :teacher_plan_id, discipline_id = :discipline_id, "
//                            "work_form_id = :work_form_id, course_id = :course_id, group_count = :group_count, "
//                            "comments = :comments, order_place = :order_place "
//                            "WHERE id = :id";

//     QString insertString = "INSERT INTO educational_work(teacher_plan_id, discipline_id, work_form_id, course_id, "
//                            "group_count, comments, order_place)"
//                            "VALUES(:teacher_plan_id, :discipline_id, :work_form_id, :course_id,"
//                            ":group_count, :comments, :order_place) ";
//     if(w->baseId()){
//         delete executeQuery(updateString, vals);
//         return w->baseId();
//     } else {
//         auto answer = executeQuery(insertString, vals);
//         answer->next();
//         work->setBaseId(answer->lastInsertId().toInt());
//         return answer->lastInsertId().toInt();
//     }
// }

// int Database::saveGenericWork(TeacherWork *work)
// {
//     auto w = dynamic_cast<GenericWork*>(work);
//     Values vals;
//     vals.insert(":id", w->baseId());
//     vals.insert(":teacher_plan_id", w->planId());
//     vals.insert(":work_form_id", w->workFormId());
//     vals.insert(":semester", w->semester());
//     vals.insert(":complite", w->complite());
//     vals.insert(":plan_hours", w->planHours());
//     vals.insert(":fact_hours", w->factHours());
//     vals.insert(":order_place", w->orderPlace());

//     QString updateString = "UPDATE generic_work "
//                            "SET work_form_id = :work_form_id, semester = :semester, "
//                            "complite = :complite, plan_hours = :plan_hours, fact_hours = :fact_hours, order_place = :order_place "
//                            "WHERE id = :id";

//     QString insertString = "INSERT INTO generic_work(teacher_plan_id, work_form_id, semester, complite, "
//                            "plan_hours, fact_hours, order_place) "
//                            "VALUES(:teacher_plan_id, :work_form_id, :semester, :complite, "
//                            ":plan_hours, :fact_hours, :order_place) ";


//     if(w->baseId()){
//         delete executeQuery(updateString, vals);
//         return w->baseId();
//     } else {
//         auto answer = executeQuery(insertString, vals);
//         answer->next();
//         work->setBaseId(answer->lastInsertId().toInt());
//         return answer->lastInsertId().toInt();
//     }
// }

// TeacherPlan * Database::requestPlan(UserPost post, int yearId)
// {
//     QString queryString = "SELECT P.id AS pid, P.status_id, P.approved_user_id, P.approved_date, P.rate, P.protocol_number, "
//                           "P.protocol_date, S.user_id, S.department_id "
//                           "FROM teacher_plan P "
//                           "INNER JOIN staff S ON S.id = P.staff_id "
//                           "WHERE staff_id = :staff_id AND year_id = :year_id";

//     Values vals;
//     vals.insert(":staff_id", post.baseId);
//     vals.insert(":year_id", yearId);

//     auto query = executeQuery(queryString, vals);

//     TeacherPlan *plan = new TeacherPlan();
//     plan->setStaff(post);
//     plan->setYearId(yearId);

//     if(query->next()){
//         plan->setBaseId(query->value("pid").toInt());
//         plan->setStatusId(query->value("status_id").toInt());
//         plan->setApproveUserId(query->value("approved_user_id").toInt());
//         plan->setApproveDate(query->value("approved_date").toDate());
//         plan->setRate(query->value("rate").toDouble());
//         plan->setProtocolNumber(query->value("protocol_number").toString());
//         plan->setProtocolDate(query->value("protocol_date").toDate());
//     }

//     return plan;
// }

// int Database::updateTeacherPlan(TeacherPlan *plan)
// {
//     Values vals;
//     vals.insert(":base_id", plan->baseId());
//     vals.insert(":staff_id", plan->getStaff().baseId);
//     vals.insert(":year_id", plan->yearId());
//     vals.insert(":status_id", plan->statusId());
//     vals.insert(":rate", plan->rate());

//     QString queryString;
//     if(plan->baseId()){
//         queryString = "UPDATE teacher_plan SET status_id = :status_id, rate = :rate WHERE id = :base_id";
//         delete executeQuery(queryString, vals);
//         return plan->baseId();
//     } else {
//         queryString = "INSERT INTO teacher_plan(staff_id, year_id, status_id, rate) "
//                       "VALUES(:staff_id, :year_id, :status_id, :rate) ";
//         auto query = executeQuery(queryString, vals);
//         query->next();
//         int id = query->lastInsertId().toInt();
//         delete query;
//         return id;
//     }
// }


Database::Database(){}
