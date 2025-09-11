#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include "user.h"

class UserManager : public QObject
{
    Q_OBJECT

public:
    explicit UserManager(QObject *parent = nullptr);

    static UserManager *get();
    bool login(const QString &login, const QString &password);
    User *getUser(int id);
    QVector<QPair<int, QString> > allUserList();
    User *user() const;
    bool userStaff(int staff);


signals:

private:
    User *m_user;

    void setUser(User *user);
};

#endif // USERMANAGER_H
