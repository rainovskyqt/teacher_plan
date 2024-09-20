#include "userrigth.h"

#include <QStringList>

UserRights::UserRights(QObject *parent)
    : QObject{parent}
{}

UserRights::UserRights(UserRights &&other)
    : QObject(other.parent()), m_rigths(std::move(other.m_rigths))
{}

UserRights &UserRights::operator=(const UserRights &other)
{
    if (this != &other) {
        m_rigths = std::move(other.m_rigths);
    }
    return *this;
}

void UserRights::add(const Right &right) {
    m_rigths.append(right);
}

QList<UserRights::Right> UserRights::items() const {
    return m_rigths;
}

UserRights UserRights::fromString(const QString &str)
{
    UserRights rights;
    auto vals = str.split(",");
    bool ok;
    foreach(auto val, vals){
        auto i = val.toInt(&ok);
        if(!ok)
            continue;
        rights.add(static_cast<Right>(i));
    }
    return rights;
}

bool UserRights::hasRight(Right right)
{
    foreach (auto r, m_rigths) {
        if(r == right)
            return true;
    }

    return false;
}

void UserRights::loadStaff()
{

}
