#include "user.h"

// #include "database/models/userrigth.h"

User::User(int id, QString surname, QString name, QString middleName) :
    m_id(id), m_surname(surname), m_name(name), m_middleName(middleName)
{

}

int User::id() const
{
    return m_id;
}

void User::setId(int newId)
{
    m_id = newId;
}

QString User::surname() const
{
    return m_surname;
}

void User::setSurname(const QString &newSurname)
{
    m_surname = newSurname;
}

QString User::name() const
{
    return m_name;
}

void User::setName(const QString &newName)
{
    m_name = newName;
}

QString User::middleName() const
{
    return m_middleName;
}

void User::setMiddleName(const QString &newMiddleName)
{
    m_middleName = newMiddleName;
}

QString User::nameFull() const
{
    return QString("%1 %2 %3").arg(m_surname, m_name, m_middleName);
}

QString User::nameShort() const
{
    return QString("%1 %2.%3.").arg(m_surname, m_name.at(0), m_middleName.at(0));
}

Staff *User::mainStaff() const
{
    foreach(auto s, m_staff){
        if(s->isMain())
            return s;
    }
    return nullptr;
}

QVector<Staff *> User::allStaff() const
{
    return m_staff;
}

void User::addStaff(Staff *newStaff)
{
    newStaff->setParent(this);
    m_staff.append(newStaff);
}

bool User::hasAnyRights(QList<UserRights::Right> rights)
{
    foreach (auto r, rights) {
        if(m_rights.hasRight(r))
            return true;
    }
    return false;
}

bool User::hasAllRights(QList<UserRights::Right> rights)
{
    foreach (auto r, rights) {
        if(!m_rights.hasRight(r))
            return false;
    }
    return true;
}




// QList<UserPost> User::posts() const
// {
//     return m_posts;
// }

// void User::addPost(int userId, int department, int post, bool main)
// {
//     m_posts.append({userId, 0, department, "", post, "", main});
// }

// void User::addPost(const UserPost &post)
// {
//     m_posts.append(post);
// }

// void User::removePost(int id)
// {
//     foreach(const UserPost p, m_posts){
//         if(p.baseId == id)
//             m_posts.removeOne(p);
//     }
// }

// void User::setRights(const UserRights &newRights)
// {
//     m_rights = newRights;
// }

// bool User::hasAnyRights(QList<UserRights::Right> rights)
// {
//     foreach (auto r, rights) {
//         if(m_rights.hasRight(r))
//             return true;
//     }
//     return false;
// }

// bool User::hasAllRights(QList<UserRights::Right> rights)
// {
//     foreach (auto r, rights) {
//         if(!m_rights.hasRight(r))
//             return false;
//     }
//     return true;
// }
