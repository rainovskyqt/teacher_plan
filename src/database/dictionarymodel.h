#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QSqlQueryModel>

class DictionaryModel : public QSqlQueryModel
{
public:

    enum Fields{
        ID,
        Name
    };

    explicit DictionaryModel(QObject *parent = nullptr);
};

#endif // DICTIONARYMODEL_H
