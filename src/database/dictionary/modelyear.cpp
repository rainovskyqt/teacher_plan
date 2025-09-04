#include "modelyear.h"

ModelYear::ModelYear(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = "SELECT id, CONCAT(begin_year, '-', end_year) AS year_text, current AS current "
                          "FROM educational_years";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}

int ModelYear::currentYearId()
{
    auto row = currentYearIndex();
    if(row)
        return data(index(row, DictionaryModel::Id)).toInt();
    return 0;
}

int ModelYear::currentYearIndex()
{
    for(int i = 0; i < rowCount(); ++i){
        if(data(index(i, 2)).toInt() == 1)
            return i;
    }

    return 0;
}
