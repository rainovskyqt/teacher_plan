#ifndef DICTIONARYADAPTER_H
#define DICTIONARYADAPTER_H

#include <QComboBox>
#include <QObject>
#include "database/database.h"

class DictionaryAdapter : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryAdapter(QObject *parent = nullptr);

    static void setDictionary(QComboBox *box, Database::DictName name);
    static void setDictionary(QList<Dictionary> &dict, Database::DictName name);
    static void setYears(QComboBox *box);

signals:
};

#endif // DICTIONARYADAPTER_H
