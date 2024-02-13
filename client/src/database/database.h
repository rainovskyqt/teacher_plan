#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "totaltime/plantime.h"
#include <QVector>
#include <QNetworkAccessManager>

#include "datamodels.h"

class Database : public QObject
{
    Q_OBJECT

public:

    enum Dictionary{
        Department,
        Post
    };

    explicit Database();
    static Database *get();
    void init(QString host, int port);
    QVector<PlanTime*> totaTimeList();
    void login(QString login, QString password);
    void requestDictionary(Dictionary name);
    void requestStaff(int userId);

public slots:

signals:
    void logged(int, QString, QString);
    void connectionError(QString);
    void dictionary(Dictionary, QMap<int, QString>);
    void staff(Staff);

private:

    QNetworkAccessManager m_manager;
    QUrl m_serverUrl;

    QString m_token;
    QString m_refreshToken;
    int baseId;

    void setHeaders(QNetworkRequest &request);
};

#endif // DATABASE_H
