#ifndef COMMENTSMANAGER_H
#define COMMENTSMANAGER_H

#include <QObject>
#include "comment.h"

class CommentsManager : public QObject
{
    Q_OBJECT
public:
    explicit CommentsManager(QObject *parent = nullptr);
    static QMap<int, Comment> loadComments(int userId, bool all);
    static void setViewed(int userId, int commentId);

signals:
};

#endif // COMMENTSMANAGER_H
