#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>

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

QVector<PlanTime *> Database::totaTimeList()
{
    QVector<PlanTime *> hours;
    hours.append(new PlanTime(1, "Учебная работа", 0, 0));
    hours.append(new PlanTime(2, "Учебно-методическая работа", 0, 0));
    hours.append(new PlanTime(3, "Научно-исследовательская работа", 0, 0));
    hours.append(new PlanTime(4, "Воспитательная и спортивная работа", 0, 0));
    hours.append(new PlanTime(5, "Другие виды работ", 0, 0));

    return hours;
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
            emit logged(doc["base_id"].toInt(), doc["token"].toString(), doc["refresh_token"].toString());
        } else {
            emit connectionError(reply->errorString());
        }
    });
}

void Database::requestDictionary(Dictionary name)
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
        QMap<int, QString> dict;
        QJsonArray doc = QJsonDocument::fromJson(reply->readAll()).array();
        for (const QJsonValue &value : doc) {
            if (!value.isObject())
                continue;

            QJsonObject obj = value.toObject();
            dict.insert(obj["base_id"].toInt(), obj["name"].toString());
        }
        emit dictionary(name, dict);
        reply->deleteLater();
    });
}

void Database::requestStaff(int userId)
{

    QNetworkRequest request;
    request.setUrl(m_serverUrl.url() + QString("/academy/staff/%1").arg(userId));
    setHeaders(request);

    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [=](){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        // for (const QJsonValue &value : doc) {
        //     if (!value.isObject())
        //         continue;

        //     QJsonObject obj = value.toObject();
        //     dict.insert(obj["base_id"].toInt(), obj["name"].toString());
        // }
        // emit dictionary(name, dict);
        qDebug() << doc;
        reply->deleteLater();
    });
}

Database::Database()
{

}

void Database::setHeaders(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"), QString("Bearer " + m_token).toLatin1());
}

