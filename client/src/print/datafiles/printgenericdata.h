#ifndef PRINTGENERICDATA_H
#define PRINTGENERICDATA_H

#include <QHash>
#include <QObject>
#include <QString>
#include "printdata.h"

class PrintGenericWork : public QObject
{
public:
    PrintGenericWork(int number, const QString &name, int plane,int fact, const QString &comments, QObject *parent = nullptr);

    int number() const;
    const QString name() const;
    int plane() const;
    int fact() const;
    const QString getComments() const;

private:
    const int m_number;
    const QString m_name;
    const int m_plane;
    const int m_fact;
    const QString m_comments;
};

class PrintGenericData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintGenericData(QObject *parent = nullptr);

    QString approvedPost() const;
    void setApprovedPost(const QString &newApprovedPost);
    QString approvedUser() const;
    void setApprovedUser(const QString &newApprovedUser);


    const QHash<int, PrintGenericWork *> works() const;

    QString department() const;
    void setDepartment(const QString &newDepartment);

private:
    QString m_approvedPost;
    QString m_approvedUser;
    QString m_department;

    QHash<int, PrintGenericWork*> m_works;           //тут QHash только для сортировки по ключу
};


#endif // PRINTGENERICDATA_H
