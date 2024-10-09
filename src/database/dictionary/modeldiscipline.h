#ifndef MODELDISCIPLINE_H
#define MODELDISCIPLINE_H

#include <QObject>
#include "database/dictionarymodel.h"

class ModelDiscipline : public DictionaryModel
{
public:
    explicit ModelDiscipline(QObject *parent = nullptr);
};

#endif // MODELDISCIPLINE_H
