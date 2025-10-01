#ifndef DATAMODELS_H
#define DATAMODELS_H

#include "userdata.h"

#include <QDate>
#include <QMap>
#include <QString>

class Dictionary
{
public:

    Dictionary(): m_id{0}, m_name{""} {}

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
    StudyYear(){
        m_begin = "2025";
        m_end = "2026";
        m_id = 0;
    }

    StudyYear(const QString &begin, const QString &end, int id){
        m_begin = begin;
        m_end = end;
        m_id = id;
    }

    QString begin() const { return m_begin; }
    QString end() const { return m_end; }
    int id() const { return m_id; }
    void setId(int newId) { m_id = newId; }

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

struct UserPost
{
    int userId;
    int baseId;
    int departmentId;
    QString depName;
    int postId;
    QString postName;
    bool main;

    bool operator==(const UserPost& other) const {
        return (this->baseId == other.baseId);
    }
};

enum UserPosts{
    LaboratoryAssistant = 1,
    SeniorLaboratoryAssistant,
    Assistant,
    Teacher,
    SeniorTeacher,
    AssociateProfessor,
    Professor,
    HeadOfDepartment,
    Dean,
    ViceRector,
    Rector
};

enum WorkType{
    Educational = 1,
    MethodicWork,
    ResearchingWork,
    SportWork,
    OtherWork
};

struct CommentsUpdate
{
    int id;
    QDate date;
    QString version;
    QString comments;
};


Q_DECLARE_METATYPE(UserPost);

#endif // DATAMODELS_H
