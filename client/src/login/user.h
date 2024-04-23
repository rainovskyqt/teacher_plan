#ifndef USER_H
#define USER_H

#include <QObject>

#include <database/datamodels.h>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    static User *get();

    int baseId() const;
    void setBaseId(int baseId);
    UserData *userData();
    QMap<int, int> posts() const;
    void addPost(int department, int post);
    void removePost(int department, int post);

private:
    int m_baseId;

    UserData m_userData;
    QMultiMap<int, int> m_posts;
};

#endif // USER_H
