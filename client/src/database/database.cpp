#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

#include <login/user.h>

Q_GLOBAL_STATIC(Database, globalInst)

Database *Database::get()
{
    return globalInst();
}

void Database::init(QString host, int port)
{
    m_serverUrl.setScheme("http");
    m_serverUrl.setHost(host);
    m_serverUrl.setPort(port);
}

void Database::login(QString login, QString password)
{
    QJsonObject params;
    params.insert("login", login);
    params.insert("password", password);

    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + "/login");
    setHeaders(request);

    QNetworkReply *reply = m_manager.post(request, QJsonDocument(params).toJson());
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        if(reply->error() == QNetworkReply::NoError){
            QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
            m_token = doc["token"].toString();
            m_refreshToken = doc["refresh_token"].toString();
            emit logged(doc["base_id"].toInt(), doc["token"].toString(), doc["refresh_token"].toString());
        } else {
            emit connectionError(reply->errorString());
        }
    });
}

void Database::requestDictionary(DictName name)
{
    QString endpoint;
    switch (name) {
    case Department: endpoint = "/departments"; break;
    case Post: endpoint = "/posts"; break;
    default:
        return;
    }

    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + "/academy" + endpoint);
    setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QList<Dictionary*> dict;
        QJsonArray doc = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : doc) {
            if (!value.isObject())
                continue;

            QJsonObject obj = value.toObject();
            dict.append(new Dictionary(obj["base_id"].toInt(), obj["name"].toString()));
        }
        emit dictionary(name, dict);
        reply->deleteLater();
    });
}

void Database::requestStaff(int userId)
{
    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + QString("/academy/staff/%1").arg(userId));
    // setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonUser = doc["user"].toObject();

        auto user = User::get();

        user->userData()->setData(
            jsonUser["login"].toString(),
            jsonUser["surname"].toString(),
            jsonUser["name"].toString(),
            jsonUser["middle_name"].toString(),
            jsonUser["rang"].toString()
            );

        QJsonObject posts = doc["posts"].toObject();
        for(auto it = posts.begin(); it != posts.end(); it++){
            user->addPost(it.key().toInt(), it.value().toInt());
        }
        emit userDataLoaded();
        reply->deleteLater();
    });
}

void Database::requestYears()
{
    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + QString("/academy/years"));

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QList<StudyYear*> yearsList;
        QJsonArray doc = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : doc) {
            if (!value.isObject())
                continue;

            QJsonObject obj = value.toObject();
            yearsList.append(new StudyYear(obj["start"].toString(), obj["end"].toString(), obj["base_id"].toInt()));
        }
        emit years(yearsList);
        reply->deleteLater();
    });
}

void Database::requestPlans(int userId)
{
    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + QString("/academy/pplan/teacher/%1").arg(userId));
    // // setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QJsonArray doc = QJsonDocument::fromJson(reply->readAll()).array();
        QList<PlansList*> plans;

        for (const QJsonValue &value : doc) {
            if (!value.isObject())
                continue;

            QJsonObject obj = value.toObject();
            plans.append(new PlansList(obj["base_id"].toInt(), obj["user_id"].toInt(),
                                       obj["year_id"].toInt(), obj["department_id"].toInt(),
                                       obj["post_id"].toInt()));
        }

        emit teacherPlans(plans);
        reply->deleteLater();
    });
}

void Database::requestPlanValues(int planId)
{
    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + QString("/academy/pplan/plan/%1").arg(planId));
    // setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        TeacherPlan* plan = new TeacherPlan();
        plan->setBaseId(doc["base_id"].toInt());
        plan->setUserId(doc["user_id"].toInt());
        plan->setDepartmentId(doc["department_id"].toInt());
        plan->setPostId(doc["post_id"].toInt());
        plan->setYearId(doc["year_id"].toInt());
        plan->setStatusId(doc["status_id"].toInt());
        plan->setRate(doc["rate"].toDouble());
        plan->setProtocolNumber(doc["protocol_number"].toString());

        QDate pDate = QDate::fromString(doc["protocol_date"].toString(), "yyyy-MM-dd");
        if(pDate.isValid())
            plan->setProtocolDate(pDate);

        QJsonObject appUser = doc["approved_user"].toObject();
        if(!appUser.isEmpty()){
            User* user = new User();
            user->setBaseId(appUser["base_id"].toInt());
            user->userData()->setData(
                appUser["login"].toString(),
                appUser["surname"].toString(),
                appUser["name"].toString(),
                appUser["middle_name"].toString(),
                appUser["rang"].toString()
                );
            plan->setApproveUser(user);
        }

        QDate aDate = QDate::fromString(doc["approved_date"].toString(), "yyyy-MM-dd");
        if(aDate.isValid())
            plan->setApproveDate(aDate);

        QMap<int, PlanTime*> planeHours;
        foreach (auto hour, doc["hours"].toArray()) {
            planeHours.insert(hour["order_place"].toInt(), new PlanTime(
                                                               hour["work_type_id"].toInt(),
                                                               hour["name"].toString(),
                                                               hour["first_semester"].toInt(),
                                                               hour["second_semester"].toInt(),
                                                               hour["base_id"].toInt(),
                                                               hour["order_place"].toInt(),
                                                               plan
                                                               ));
        }
        plan->setHours(planeHours);

        emit planValues(plan);
        reply->deleteLater();
    });
}

void Database::updateTeacherPlan(TeacherPlan *plan)
{
    QString point = m_serverUrl.url() + "/academy/pplan/plan";

    QVariantMap planeMap;
    planeMap.insert("base_id", plan->baseId());
    planeMap.insert("user_id", plan->userId());
    planeMap.insert("department_id", plan->departmentId());
    planeMap.insert("post_id", plan->postId());
    planeMap.insert("year_id", plan->yearId());
    planeMap.insert("status_id", plan->statusId());
    if(plan->approveUser()){
        planeMap.insert("approved_user_id", plan->approveUser()->baseId());
        planeMap.insert("approved_date", plan->approveDate().toString("yyyy-MM-dd"));
    }
    planeMap.insert("rate", plan->rate());
    if(plan->protocolDate().isValid()){
        planeMap.insert("protocol_number", plan->protocolNumber());
        planeMap.insert("protocol_date", plan->protocolDate().toString("yyyy-MM-dd"));
    }
    QJsonArray hours;
    auto planeHours = plan->hours();
    for (auto hour = planeHours.begin(); hour != planeHours.end(); ++hour) {
        QVariantMap hourMap;
        hourMap.insert("base_id", hour.value()->baseId());
        hourMap.insert("plan_id", plan->baseId());
        hourMap.insert("work_type_id", hour.value()->workType());
        hourMap.insert("first_semester", hour.value()->semesterHours(PlanTime::FirstSemester));
        hourMap.insert("second_semester", hour.value()->semesterHours(PlanTime::SecondSemestr));
        hourMap.insert("name", hour.value()->name());
        hourMap.insert("order_place", hour.key());
        hours.append(QJsonValue(QJsonObject::fromVariantMap(hourMap)));
    }
    planeMap.insert("hours", hours);

    inputToServer(point, QJsonDocument::fromVariant(planeMap), true, PlanId);
}

void Database::updateUser(User *user)
{
    QString point = m_serverUrl.url() + "/user";
    QVariantMap userMap;
    userMap.insert("base_id", user->baseId());
    userMap.insert("login", user->userData()->login());
    userMap.insert("password", user->userData()->password());
    userMap.insert("surname", user->userData()->surname());
    userMap.insert("name", user->userData()->name());
    userMap.insert("middle_name", user->userData()->middle_name());
    userMap.insert("rang", user->userData()->rang());

    QJsonArray posts;
    auto userPosts = user->posts();
    for (auto post = userPosts.begin(); post != userPosts.end(); ++post) {
        QVariantMap postMap;
        postMap.insert("base_id", 0);
        postMap.insert("department_id", post.key());
        postMap.insert("post_id", post.value());
        posts.append(QJsonValue(QJsonObject::fromVariantMap(postMap)));
    }

    userMap.insert("posts", posts);
    inputToServer(point, QJsonDocument::fromVariant(userMap), false);
}

void Database::setHeaders(QNetworkRequest &request, Marks mark)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer " + m_token).toLatin1());
}

void Database::inputToServer(QString point, QJsonDocument values, bool update, Marks mark)
{
    QNetworkRequest request;
    setHeaders(request, mark);
    request.setUrl(point);

    QNetworkReply* reply;

    if(update)
        reply = m_manager.put(request, values.toJson());
    else
        reply = m_manager.post(request, values.toJson());

    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    auto json = reply->readAll();

    switch(mark){
    case PlanId:
        emit newPlaneId(json.toInt());
        break;
    case Other:
        break;
    }

    if (reply->error() != QNetworkReply::NoError)
        qDebug() << "Network error: " << reply->error();
    qDebug() << "Добавление завершено";

}

Database::Database(){}
