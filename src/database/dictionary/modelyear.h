#ifndef MODELYEAR_H
#define MODELYEAR_H

#include "dictionarymodel.h"

class ModelYear : public DictionaryModel
{
public:
    explicit ModelYear(QObject *parent = nullptr);

    int currentYear();
};

#endif // MODELYEAR_H
