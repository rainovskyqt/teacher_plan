#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    static User *get();

    void setData(int baseId, const QString &token, const QString &refreshToken);
    int baseId() const;
    void setBaseId(int baseId);
    QString token() const;
    void setToken(const QString &token);
    QString refreshToken() const;
    void setRefreshToken(const QString &refreshToken);

private:
    int m_baseId;
    QString m_token;
    QString m_refreshToken;
};

#endif // USER_H
