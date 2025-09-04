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

int ModelDepartment::departmentIndex(int depId)
{
    for(int i = 0; i < rowCount(); ++i){
        if(data(index(i, 0)).toInt() == depId)
            return i;
    }

    return 0;
}
