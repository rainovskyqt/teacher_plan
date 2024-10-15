#include "modeldiscipline.h"
#include <QDebug>
ModelDiscipline::ModelDiscipline(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, `name` "
                          "FROM discipline "
                          "ORDER BY `name`";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
