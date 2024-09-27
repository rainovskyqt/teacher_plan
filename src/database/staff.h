#ifndef STAFF_H
#define STAFF_H

#include <QObject>

class Staff : public QObject
{
    Q_OBJECT

public:
    explicit Staff(int id, int departmentId, QString departmentName, int postId, QString postName,
                   bool main, QObject *parent = nullptr);
    ~Staff() {}

    const int id() const;
    const int departmentId() const;
    const QString &departmentName() const;
    const int postId() const;
    const QString &postName() const;
    bool isMain() const;

private:
    const int m_id;
    const int m_departmentId;
    const QString m_departmentName;
    const int m_postId;
    const QString m_postName;
    const bool m_main;
};

#endif // STAFF_H
