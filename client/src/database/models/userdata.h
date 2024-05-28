#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{

public:
    explicit UserData();
    UserData(const UserData &other);

    void setData(const QString &login, const QString &surname, const QString &name, const QString &middle_name = "",
                 const QString &rang = "");

    QString login() const;
    QString surname() const;
    QString name() const;
    QString middle_name() const;
    QString rang() const;

private:
    QString m_login;
    QString m_surname;
    QString m_name;
    QString m_middle_name;
    QString m_rang;
};

#endif // USERDATA_H
