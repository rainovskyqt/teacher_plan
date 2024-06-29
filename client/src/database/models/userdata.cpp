#include "userdata.h"

UserData::UserData() {}

void UserData::setData(const QString &login, const QString &surname, const QString &name, const QString &middle_name,
                       const QString &rang, int rangId, const QString &password){
    m_login = login;
    m_surname = surname;
    m_name = name;
    m_middle_name = middle_name;
    m_rang = rang;
    m_password = password;
    m_rangId = rangId;
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

int UserData::rangId() const
{
    return m_rangId;
}

QString UserData::password() const
{
    return m_password;
}
