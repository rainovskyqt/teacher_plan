#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{

public:
    explicit UserData();

    void setData(const QString &login, const QString &surname, const QString &name, const QString &middle_name = "",
                 const QString &rang = "", int rangId = 0, const QString &password = "");

    QString login() const;
    QString surname() const;
    QString name() const;
    QString middle_name() const;
    QString rang() const;
    int rangId() const;

    QString password() const;

private:
    QString m_login;
    QString m_password;
    QString m_surname;
    QString m_name;
    QString m_middle_name;
    QString m_rang;
    int m_rangId;
};

#endif // USERDATA_H
