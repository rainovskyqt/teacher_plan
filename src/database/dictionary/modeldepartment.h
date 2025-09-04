#ifndef MODELDEPARTMENT_H
#define MODELDEPARTMENT_H

#include "dictionarymodel.h"

class ModelDepartment : public DictionaryModel
{
public:
    explicit ModelDepartment(QObject *parent = nullptr);

    int departmentIndex(int depId);
};

#endif // MODELDEPARTMENT_H
