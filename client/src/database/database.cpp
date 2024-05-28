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
    // setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QJsonArray doc = QJsonDocument::fromJson(reply->readAll()).array();
        QList<TeacherPlan*> plans;

        for (const QJsonValue &value : doc) {
            if (!value.isObject())
                continue;

            TeacherPlan* plan = new TeacherPlan();
            QJsonObject obj = value.toObject();
            plan->setBaseId(obj["base_id"].toInt());
            plan->setUserId(obj["user_id"].toInt());
            plan->setDepartmentId(obj["department_id"].toInt());
            plan->setPostId(obj["post_id"].toInt());
            plan->setYearId(obj["year_id"].toInt());
            plan->setStatusId(obj["status_id"].toInt());
            plan->setRate(obj["rate"].toDouble());
            plan->setProtocolNumber(obj["protocol_number"].toString());

            QDate pDate = QDate::fromString(obj["protocol_date"].toString(), "yyyy-MM-dd");
            if(pDate.isValid())
                plan->setProtocolDate(pDate);

            QJsonObject appUser = obj["approved_user"].toObject();
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

            QDate aDate = QDate::fromString(obj["approved_date"].toString(), "yyyy-MM-dd");
            if(aDate.isValid())
                plan->setApproveDate(aDate);

            QMap<int, PlanTime*> planeHours;
            foreach (auto hour, obj["hours"].toArray()) {
                planeHours.insert(hour["order_place"].toInt(), new PlanTime(
                                                                   hour["work_type_id"].toInt(),
                                                                   hour["name"].toString(),
                                                                   hour["first_semester"].toInt(),
                                                                   hour["second_semester"].toInt(),
                                                                   hour["base_id"].toInt(),
                                                                   plan
                                                                   ));
            }
            plan->setHours(planeHours);

            plans.append(plan);
        }

        emit teacherPlans(plans);
        reply->deleteLater();
    });
}

void Database::updateTeacherPlan(TeacherPlan *plan)
{
    QString point = m_serverUrl.url() + "/academy/pplan/plan";

    QVariantMap vmap;
    vmap.insert("base_id", plan->baseId());
    vmap.insert("status_id", plan->statusId());
    if(plan->approveUser()){
        vmap.insert("approved_user_id", plan->approveUser()->baseId());
        vmap.insert("approved_date", plan->approveDate().toString("yyyy-MM-dd"));
    }
    vmap.insert("rate", plan->rate());
    if(plan->protocolDate().isValid()){
        vmap.insert("protocol_number", plan->protocolNumber());
        vmap.insert("protocol_date", plan->protocolDate().toString("yyyy-MM-dd"));
    }
    // vmap.insert("department_boss_sign", plan->);

    inputToServer(point, vmap, true);
}

Database::Database()
{

}

void Database::setHeaders(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer " + m_token).toLatin1());
}

void Database::inputToServer(QString point, QVariantMap values, bool update)
{
    QNetworkRequest request;
    setHeaders(request);
    QJsonDocument json = QJsonDocument::fromVariant(values);
    request.setUrl(point);

    QNetworkReply* reply;
    if(update)
        reply = m_manager.put(request, json.toJson());
    else
        reply = m_manager.post(request, json.toJson());

    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError)
        qDebug() << "Network error: " << reply->error();
    qDebug() << "Добавление завершено";

}

