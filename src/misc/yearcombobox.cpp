#include "yearcombobox.h"

#include <database/dictionary/dictionarymanager.h>

YearCombobox::YearCombobox(QWidget *parent) : QComboBox(parent)
{
    init();
}

int YearCombobox::selectedYear()
{
    return model()->data(model()->index(currentIndex(), 0)).toInt();
}

void YearCombobox::init()
{
    setCurrentYear();

    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int row){
        int id = model()->data(model()->index(row, 0)).toInt();
        emit yearChanged(id);
    });
}

void YearCombobox::setCurrentYear()
{
    auto years = DictionaryManager::get()->years();
    setModel(years);
    setModelColumn(DictionaryModel::Name);
    setCurrentIndex(years->currentYearIndex());
}
