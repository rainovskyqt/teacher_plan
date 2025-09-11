#include "dictionarymodel.h"

DictionaryModel::DictionaryModel(QObject *parent)
    : QSqlQueryModel{parent}
{}

int DictionaryModel::idRowIndex(int depId)
{
    for(int i = 0; i < rowCount(); ++i){
        if(data(index(i, 0)).toInt() == depId)
            return i;
    }

    return 0;
}
