#include "user.h"

Q_GLOBAL_STATIC(User, globalInst)

User *User::get()
{
    return globalInst();
}

void User::setData(int baseId, const QString &token, const QString &refreshToken)
{
    setBaseId(baseId);
    setToken(token);
    setRefreshToken(refreshToken);
}

int User::baseId() const
{
    return m_baseId;
}

void User::setBaseId(int baseId)
{
    m_baseId = baseId;
}

QString User::token() const
{
    return m_token;
}

void User::setToken(const QString &token)
{
    m_token = token;
}

QString User::refreshToken() const
{
    return m_refreshToken;
}

void User::setRefreshToken(const QString &refreshToken)
{
    m_refreshToken = refreshToken;
}

User::User() {}
