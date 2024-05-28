#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QObject>

#include "database/models/userdata.h"

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    User(const User &other);

    static User *get();

    int baseId() const;
    void setBaseId(int baseId);
    UserData *userData();
    QMultiMap<int, int> posts() const;
    void addPost(int department, int post);
    void removePost(int department, int post);

private:
    int m_baseId;

    UserData m_userData;
    QMultiMap<int, int> m_posts;
};

#endif // USER_H
