#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "database/models/plantime.h"
#include <QVector>
#include <QNetworkAccessManager>

#include "models/datamodels.h"
#include "models/teacherplan.h"

class Database : public QObject
{
    Q_OBJECT

public:

    enum DictName{
        Department,
        Post
    };

    explicit Database();
    static Database *get();
    void init(QString host, int port);
    QVector<PlanTime*> totalTimeList();
    void login(QString login, QString password);
    void requestDictionary(DictName name);
    void requestStaff(int userId);
    void requestYears();
    void requestPlans(int userId);
    void requestPlanValues(int planeId);
    void updateTeacherPlan(TeacherPlan *plan);

public slots:

signals:
    void logged(int, QString, QString);
    void connectionError(QString);
    void dictionary(DictName, QList<Dictionary*>);
    void userDataLoaded();
    void years(QList<StudyYear*>);
    void teacherPlans(QList<TeacherPlan*>);

private:

    QNetworkAccessManager m_manager;
    QUrl m_serverUrl;

    QString m_token;
    QString m_refreshToken;
    int baseId;

    void setHeaders(QNetworkRequest &request);
    void inputToServer(QString point, QVariantMap values, bool update);
};

#endif // DATABASE_H
