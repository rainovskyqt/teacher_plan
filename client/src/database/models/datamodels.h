#ifndef DATAMODELS_H
#define DATAMODELS_H

#include "userdata.h"

#include <QMap>
#include <QString>

class Dictionary
{
public:

    Dictionary(int id, const QString &name)
    {
        m_id = id;
        m_name = name;
    }

    int id() const { return m_id; }
    QString name() const{ return m_name; }

private:
    int m_id;
    QString m_name;
};

class StudyYear
{
public:
    StudyYear(const QString &begin, const QString &end, int id){
        m_begin = begin;
        m_end = end;
        m_id = id;
    }

    QString begin() const { return m_begin; }
    QString end() const { return m_end; }
    int id() const { return m_id; }

private:
    QString m_begin;
    QString m_end;
    int m_id;
};

class Staff
{
public:
    Staff() {}

private:
    UserData m_user;
    QMap<Dictionary, Dictionary> m_posts;
};

enum WorkType{
    Educational = 1,
    MethodicWork,
    SearchingWork,
    SportWork,
    OtherWork
};

#endif // DATAMODELS_H
