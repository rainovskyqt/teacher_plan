#ifndef USER_H
#define USER_H

#include <QMultiMap>
#include <QObject>

#include "database/models/userdata.h"
#include "database/models/datamodels.h"
#include "database/models/userrigth.h"

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();

    int baseId() const;
    void setBaseId(int baseId);
    UserData *userData();
    QList<UserPost> posts() const;
    void addPost(int userId, int department, int post, bool main);
    void addPost(const UserPost &post);
    void removePost(int id);

    void setRights(const UserRights &newRights);
    bool hasAnyRights(QList<UserRights::Right> rights);
    bool hasAllRights(QList<UserRights::Right> rights);

private:
    int m_baseId;

    UserData m_userData;
    QList<UserPost> m_posts;
    UserRights m_rights;
};

#endif // USER_H
