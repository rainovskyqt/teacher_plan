#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QSqlQueryModel>

#include "database/database.h"

class DictionaryModel : public QSqlQueryModel
{
public:

    enum Fields{
        Id,
        Name,
        WorkType,
        Chapter,
        MaxYearCount
    };

    explicit DictionaryModel(QObject *parent = nullptr);

};

#endif // DICTIONARYMODEL_H
