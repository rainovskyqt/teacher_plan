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
    QSqlQuery selectQuery(QString queryString, Arguments args = {});
    int insertQuery(QString queryString, Arguments args = {});
    void updateDeleteQuery(QString queryString, Arguments args = {});
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

public slots:

signals:

private slots:

private:
    QString m_lastError;
    QSqlQuery executeQuery(QString queryString, Arguments args);

    // int getId(QString json);
    // int saveEducationalWork(TeacherWork *work);
    // int saveGenericWork(TeacherWork *work);
};

#endif // DATABASE_H
