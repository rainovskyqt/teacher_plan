#include "modelgenericworkform.h"

ModelGenericWorkForm::ModelGenericWorkForm(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, CONCAT(chapter, ' ', `name`), work_type, max_year_count, max_unit_count "
                          "FROM generic_work_form";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
