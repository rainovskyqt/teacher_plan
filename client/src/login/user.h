#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QObject>

#include "database/models/userdata.h"
#include "database/models/datamodels.h"

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();

    int baseId() const;
    void setBaseId(int baseId);
    UserData *userData();
    QList<UserPost> posts() const;
    void addPost(int userId, int department, int post, int id = 0);
    void removePost(int id);

private:
    int m_baseId;

    UserData m_userData;
    QList<UserPost> m_posts;
};

#endif // USER_H
