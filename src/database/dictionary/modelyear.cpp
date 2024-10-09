#include "modelyear.h"

ModelYear::ModelYear(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, CONCAT(begin_year, '-', end_year) AS year_text "
                          "FROM educational_years";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
