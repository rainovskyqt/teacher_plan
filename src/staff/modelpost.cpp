#include "modelpost.h"

#include "database/database.h"

ModelPost::ModelPost(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, `name` "
                          "FROM post "
                          "ORDER BY `name`";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
