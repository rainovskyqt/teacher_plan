#ifndef DATABASE_H
#define DATABASE_H

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QObject>

#include "database/models/plantime.h"
#include <QVector>

#include "models/datamodels.h"
#include "models/teacherplan.h"
#include <QSqlQuery>

using Values = QMap<QString, QVariant>;
using Hours = QMap<int, PlanTime*>;


class Database : public QObject
{
    Q_OBJECT

public:

    enum DictName{
        Department,
        Post,
        Rang
    };

    explicit Database();
    static Database *get();
    bool init(QString host, int port);
    int addUser(User *user);
    void addPosts(QMultiMap<int, int> posts, int userId);
    int addPost(int userId, int departmentId, int postId);
    User *login(QString login, QString password);
    QList<Dictionary> getDictionary(DictName name);
    QList<StudyYear> getYears();
    TeacherPlan *requestPlan(int userId, int yearId, int departmentId, int postId);
    void updateTeacherPlan(TeacherPlan *plan);

    QString encodePassword(QString password);

    const QString &lastError() const;

public slots:

signals:
    // void logged(int, QString, QString);
    // void connectionError(QString);
    // void dictionary(DictName, QList<Dictionary*>);
    // void userDataLoaded();
    // void years(QList<StudyYear*>);
    // void teacherPlans(QList<PlansList*>);
    // void planValues(TeacherPlan*);
    // void newPlaneId(int);

private slots:

private:

    enum Marks{
        Other = 1,
        PlanId
    };

    QString m_token;
    QString m_refreshToken;
    int baseId;
    QString m_lastError;

    QSqlQuery *executeQuery(QString queryString, Values vals = {});
    Hours getDefaultHours();

    void setHeaders(QNetworkRequest &request, Marks mark = Other);
    int getId(QString json);
//    void updateHours(Hours hours, int planId);
};

#endif // DATABASE_H
