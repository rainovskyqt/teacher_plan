#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QVector>
#include <QSqlQuery>
#include <QMap>

// #include "models/datamodels.h"
// #include "models/teacherplan.h"

// #include <database/models/teacherwork.h>
// #include <educationwork/educationalhour.h>
// #include "database/models/datamodels.h"

// #include <database/models/genericwork.h>



class EducationalWork;
class GenericWorkForm;

using Arguments = QMap<QString, QVariant>;

class Database : public QObject
{
    Q_OBJECT

public:

    using Values = QMap<QString, QVariant>;
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
    QSqlQuery *executeQuery(QString queryString, Values vals = {});
    const QString &lastError() const;


    // User *login(QString login, QString password, int id = 0);

    // int addUser(User *user);
    // void addPosts(QList<UserPost> posts, int userId);
    // int addPost(UserPost post, int userId);
    // QVector<Dictionary> getDictionary(DictName name);
    // QList<StudyYear> getYears();
    // TeacherPlan *requestPlan(UserPost post, int yearId);
    // int updateTeacherPlan(TeacherPlan *plan);
    // QVector<EducationalWork *> educationWork(int planId);
    // QVector<GenericWork *> genericWork(int planId, WorkType type);
    // int saveWork(TeacherWork *work);
    // void deleteWork(TeacherWork *work);
    // QList<EducationalHour*> getEdcationalHours(int workId);
    // int saveEdcationalHour(EducationalHour* hour);
    // QList<GenericWorkForm *> getWorks(WorkType type);
    // QMap<int, CommentsUpdate> updateComments(bool all, int userId);
    // void setViewed(int userId, int commentId);

public slots:

signals:

private slots:

private:
    int baseId;
    QString m_lastError;
    // int getId(QString json);
    // int saveEducationalWork(TeacherWork *work);
    // int saveGenericWork(TeacherWork *work);
};

#endif // DATABASE_H
