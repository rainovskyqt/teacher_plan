#ifndef DATABASE_H
#define DATABASE_H

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QObject>
#include <QVector>

#include "models/datamodels.h"
#include "models/teacherplan.h"
#include <QSqlQuery>

#include <database/models/teacherwork.h>
#include <educationwork/educationalhour.h>
#include "database/models/datamodels.h"

#include <database/models/genericwork.h>


using Values = QMap<QString, QVariant>;

class EducationalWork;
class GenericWorkForm;

class Database : public QObject
{
    Q_OBJECT

public:

    enum DictName{
        Department,
        Post,
        Rang,
        Discipline,
        Course,
        WorkForm
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
    int updateTeacherPlan(TeacherPlan *plan);
    QString encodePassword(QString password);
    const QString &lastError() const;
    QVector<EducationalWork *> educationWork(int planId);
    QVector<GenericWork *> genericWork(int planId);
    void saveWork(TeacherWork *work);
    void deleteWork(TeacherWork *work);
    QList<EducationalHour*> getEdcationalHours(int workId);
    int saveEdcationalHour(EducationalHour* hour);
    QList<GenericWorkForm *> getWorks(WorkType type);

public slots:

signals:

private slots:

private:
    int baseId;
    QString m_lastError;
    QSqlQuery *executeQuery(QString queryString, Values vals = {});
    int getId(QString json);
    void saveEducationalWork(TeacherWork *work);
    void saveGenericWork(TeacherWork *work);
};

#endif // DATABASE_H
