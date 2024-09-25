#ifndef USERRIGTH_H
#define USERRIGTH_H

#include <QObject>
#include <QString>

class UserRights : public QObject
{
    Q_OBJECT

public:

    enum Right{
        DepartmentTeacherPlans = 1,
        AllTeacherPlans,
        OwnTeacherPlans
    };

    explicit UserRights(QObject *parent = nullptr);
    UserRights(UserRights&& other) ;
    UserRights &operator=(const UserRights& other);

    void add(const Right &right);
    QList<Right> items() const;

    static UserRights fromString(const QString &str);
    bool hasRight(Right right);

signals:

private:
    QList<Right> m_rigths;
};

#endif // USERRIGTH_H
