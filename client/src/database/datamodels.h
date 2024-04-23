#ifndef DATAMODELS_H
#define DATAMODELS_H

#include <QMap>
#include <QString>

struct Dictionary
{
    Dictionary() {}
public:
    int id;
    QString name;
};

struct UserData
{
    UserData() {}
public:
    void setData(QString login, QString surname, QString name, QString middle_name){
        m_login = login;
        m_surname = surname;
        m_name = name;
        m_middle_name = middle_name;}

    QString login() const {return m_login;}
    QString surname() const {return m_surname;}
    QString name() const {return m_name;}
    QString middle_name() const {return m_middle_name;}

private:
    QString m_login;
    QString m_surname;
    QString m_name;
    QString m_middle_name;
};

struct Staff
{
    Staff() {}
    UserData user;
    QMap<Dictionary, Dictionary> posts;
};

#endif // DATAMODELS_H
