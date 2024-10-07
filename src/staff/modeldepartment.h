#ifndef MODELDEPARTMENT_H
#define MODELDEPARTMENT_H

#include "database/dictionarymodel.h"

class ModelDepartment : public DictionaryModel
{
public:
    explicit ModelDepartment(QObject *parent = nullptr);
};

#endif // MODELDEPARTMENT_H
