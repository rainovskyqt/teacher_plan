#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User();
    static User *get();

    int baseId() const;
    void setBaseId(int baseId);

private:
    int m_baseId;
};

#endif // USER_H
