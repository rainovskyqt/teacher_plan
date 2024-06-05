#include "user.h"

Q_GLOBAL_STATIC(User, globalInst)

User *User::get()
{
    return globalInst();
}

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

QMultiMap<int, int> User::posts() const
{
    return m_posts;
}

void User::addPost(int department, int post)
{
    m_posts.insert(department, post);
}

void User::removePost(int department, int post)
{
    m_posts.remove(department, post);
}

User::User() {m_baseId = 0;}
