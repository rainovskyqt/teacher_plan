#include "dictionaryadapter.h"

DictionaryAdapter::DictionaryAdapter(QObject *parent)
    : QObject{parent}
{}

void DictionaryAdapter::setDictionary(QComboBox *box, Database::DictName name)
{
    box->clear();

    auto database = Database::get();

    auto dict = database->getDictionary(name);

    box->addItem("-", 0);
    foreach (auto row, dict) {
        box->addItem(row.name(), row.id());
    }
}

void DictionaryAdapter::setDictionary(QList<Dictionary> &dict, Database::DictName name)
{
    dict.clear();

    auto database = Database::get();
    auto dictBase = database->getDictionary(name);

    foreach (auto row, dictBase) {
        dict.append(Dictionary(row.id(), row.name()));
    }
}

void DictionaryAdapter::setYears(QComboBox *box)
{
    auto database = Database::get();
    auto years = database->getYears();

    box->clear();

    foreach (auto year, years) {
        box->addItem(QString("%1 - %2").arg(year.begin(), year.end()), year.id());
    }
}
