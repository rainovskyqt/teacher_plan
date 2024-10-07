#ifndef MODELYEAR_H
#define MODELYEAR_H

#include "database/dictionarymodel.h"

class ModelYear : public DictionaryModel
{
public:
    explicit ModelYear(QObject *parent = nullptr);
};

#endif // MODELYEAR_H
