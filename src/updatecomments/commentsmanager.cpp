#include "commentsmanager.h"

#include "database/database.h"

#include <QVariant>

CommentsManager::CommentsManager(QObject *parent)
    : QObject{parent}
{}

QMap<int, Comment> CommentsManager::loadComments(int userId, bool all)
{
    QString queryString = "SELECT id, `version`, `date`, comments "
                          "FROM update_comments";
    if(!all)
        queryString.append(
            " WHERE id > "
            "(IFNULL((SELECT last_coments_id "
            "FROM user_update_comments WHERE user_id = :user_id), 0))");
    Arguments arg;
    arg.insert(":user_id", QVariant::fromValue(userId));
    auto query = Database::get()->selectQuery(queryString, arg);

    QMap<int, Comment> comments;
    while (query.next()) {
        Comment comment;
        int id = query.value("id").toInt();
        comment.setId(id);
        comment.setDate(query.value("date").toDate());
        comment.setVersion(query.value("version").toString());
        comment.setComment(query.value("comments").toString());
        comments.insert(id, comment);
    }
    return comments;
}

void CommentsManager::setViewed(int userId, int commentId)
{
        QString queryString = "INSERT INTO user_update_comments (user_id, last_coments_id) "
                              "VALUES (:user_id, :last_coments_id) AS new_val "
                              "ON DUPLICATE KEY UPDATE last_coments_id = new_val.last_coments_id";

        Arguments arg;
        arg.insert(":user_id", userId);
        arg.insert(":last_coments_id", commentId);
        Database::get()->updateDeleteQuery(queryString, arg);
}
