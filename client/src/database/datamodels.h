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
    int id;
    QString login;
    QString surname;
    QString name;
    QString middle_name;
};


struct Staff
{
    Staff() {}
    UserData user;
    QMap<Dictionary, Dictionary> posts;
};

#endif // DATAMODELS_H
