#ifndef MODELWORKFORM_H
#define MODELWORKFORM_H

#include <QObject>
#include "dictionarymodel.h"

class ModelWorkForm : public DictionaryModel
{
public:
    explicit ModelWorkForm(QObject *parent = nullptr);
};

#endif // MODELWORKFORM_H