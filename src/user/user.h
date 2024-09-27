#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QObject>

#include "database/staff.h"

#include "userrigth.h"

// #include "database/models/userdata.h"
// #include "database/models/datamodels.h"
// #include "database/models/userrigth.h"

class User : public QObject
{
    Q_OBJECT

public:
    explicit User(int id = 0, QString surname = QString(), QString name = QString(), QString middleName = QString());

    // QList<UserPost> posts() const;
    // void addPost(int userId, int department, int post, bool main);
    // void addPost(const UserPost &post);
    // void removePost(int id);

    // void setRights(const UserRights &newRights);
    // bool hasAnyRights(QList<UserRights::Right> rights);
    // bool hasAllRights(QList<UserRights::Right> rights);

    int id() const;
    void setId(int newId);

    QString surname() const;
    void setSurname(const QString &newSurname);

    QString name() const;
    void setName(const QString &newName);

    QString middleName() const;
    void setMiddleName(const QString &newMiddleName);

    QString nameFull() const;
    QString nameShort() const;

    Staff *mainStaff() const;
    QVector<Staff*> allStaff() const;
    void addStaff(Staff* newStaff);

    bool hasAnyRights(QList<UserRights::Right> rights);
    bool hasAllRights(QList<UserRights::Right> rights);

private:
    int m_id;
    QString m_surname;
    QString m_name;
    QString m_middleName;

    QVector<Staff*> m_staff;
    UserRights m_rights;

};

#endif // USER_H
