#include "user.h"

#include "database/models/userrigth.h"

int User::baseId() const
{
    return m_baseId;
}

void User::setBaseId(int baseId)
{
    m_baseId = baseId;
}

UserData *User::userData()
{
    return &m_userData;
}

QList<UserPost> User::posts() const
{
    return m_posts;
}

void User::addPost(int userId, int department, int post, bool main)
{
    m_posts.append({userId, 0, department, "", post, "", main});
}

void User::addPost(const UserPost &post)
{
    m_posts.append(post);
}

void User::removePost(int id)
{
    foreach(const UserPost p, m_posts){
        if(p.baseId == id)
            m_posts.removeOne(p);
    }
}

void User::setRights(const UserRights &newRights)
{
    m_rights = newRights;
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

User::User() {m_baseId = 0;}
