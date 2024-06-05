#include "userdata.h"

UserData::UserData() {}

UserData::UserData(const UserData &other) {
    m_login = other.m_login;
    m_surname = other.m_surname;
    m_name = other.m_name;
    m_middle_name = other.m_middle_name;
    m_rang = other.m_rang;
}

void UserData::setData(const QString &login, const QString &surname, const QString &name, const QString &middle_name,
                       const QString &rang, const QString &password){
    m_login = login;
    m_surname = surname;
    m_name = name;
    m_middle_name = middle_name;
    m_rang = rang;
    m_password = password;
}

QString UserData::login() const {
    return m_login;
}

QString UserData::surname() const {
    return m_surname;
}

QString UserData::name() const {
    return m_name;
}

QString UserData::middle_name() const {
    return m_middle_name;
}

QString UserData::rang() const {
    return m_rang;
}

QString UserData::password() const
{
    return m_password;
}
