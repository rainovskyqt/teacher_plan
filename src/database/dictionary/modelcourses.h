#ifndef MODELCOURSES_H
#define MODELCOURSES_H

#include <QObject>
#include "dictionarymodel.h"

class ModelCourses : public DictionaryModel
{
public:
    explicit ModelCourses(QObject *parent = nullptr);
};

#endif // MODELCOURSES_H