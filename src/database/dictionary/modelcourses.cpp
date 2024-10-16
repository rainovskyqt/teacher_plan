#include "modelcourses.h"

ModelCourses::ModelCourses(QObject *parent)
    : DictionaryModel{parent}
{
    QString queryString = R"(SELECT id, `name`
                             FROM course
                             ORDER BY `name`)";

    auto query = Database::get()->selectQuery(queryString);
    setQuery(query);
}
