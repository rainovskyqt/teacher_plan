#ifndef MODELYEAR_H
#define MODELYEAR_H

#include "dictionarymodel.h"

class ModelYear : public DictionaryModel
{
public:
    explicit ModelYear(QObject *parent = nullptr);

    int currentYearIndex();
    int currentYearId();
};

#endif // MODELYEAR_H
