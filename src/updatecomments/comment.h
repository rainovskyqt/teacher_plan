#ifndef COMMENT_H
#define COMMENT_H

#include <QDate>

class Comment
{

public:
    explicit Comment();
    explicit Comment(const Comment &other);
    ~Comment() {}

    void operator=(const Comment &other);

    int id() const;
    void setId(int newId);
    QDate date() const;
    QString dateString() const;
    void setDate(const QDate &newDate);
    QString version() const;
    void setVersion(const QString &newVersion);
    QString comment() const;
    void setComment(const QString &newComment);

private:
    int m_id;
    QDate m_date;
    QString m_version;
    QString m_comment;
};

#endif // COMMENT_H
