#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>

class User;

class UserManager : public QObject
{
    Q_OBJECT

public:
    explicit UserManager(QObject *parent = nullptr);

    static UserManager *get();
    bool login(const QString &login, const QString &password);
    User *user();

signals:

private:
    User *m_user;
};

#endif // USERMANAGER_H
