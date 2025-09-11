#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QSqlQueryModel>

#include "database/database.h"

class DictionaryModel : public QSqlQueryModel
{
    Q_OBJECT

public:

    enum Fields{
        Id,
        Name,
        WorkType,
        Chapter,
        MaxYearCount
    };

    explicit DictionaryModel(QObject *parent = nullptr);

    int idRowIndex(int depId);

};

#endif // DICTIONARYMODEL_H
