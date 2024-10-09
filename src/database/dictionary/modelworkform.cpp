#include "modelworkform.h"

ModelWorkForm::ModelWorkForm(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, `name` "
                          "FROM educational_work_form "
                          "ORDER BY `name`";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
