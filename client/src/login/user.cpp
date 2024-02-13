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

User::User() {}
