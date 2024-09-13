#include "user.h"

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

void User::addPost(int userId, int department, int post, int id)
{
    m_posts.append({userId, id, department, post});
}

void User::removePost(int id)
{
    foreach(const UserPost p, m_posts){
        if(p.baseId == id)
            m_posts.removeOne(p);
    }
}

User::User() {m_baseId = 0;}
