#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QObject>

#include "database/staff.h"

#include "userrigth.h"

class User : public QObject
{
    Q_OBJECT

public:
    explicit User(int id = 0, QString surname = QString(), QString name = QString(), QString middleName = QString());
    ~User() {}

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

    void setRights(const UserRights &newRights);
    void setRights(const QString &newRights);
    void addRights(const QString &rights);


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
