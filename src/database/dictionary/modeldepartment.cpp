#include "modeldepartment.h"

ModelDepartment::ModelDepartment(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, `name` "
                          "FROM department "
                          "ORDER BY `name`";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
