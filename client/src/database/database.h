#ifndef DATABASE_H
#define DATABASE_H

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QObject>
#include <QVector>

#include "models/datamodels.h"
#include "models/teacherplan.h"
#include <QSqlQuery>

using Values = QMap<QString, QVariant>;

class EducationalWork;

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
    QVector<EducationalWork *> educationWork(int planId);

public slots:

signals:

private slots:

private:
    int baseId;
    QString m_lastError;
    QSqlQuery *executeQuery(QString queryString, Values vals = {});
    int getId(QString json);

};

#endif // DATABASE_H
