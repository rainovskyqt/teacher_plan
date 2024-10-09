#include "combobox.h"

#include <QStringListModel>

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent) {
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(completer);
    updateCompleterModel();
}

void ComboBox::addItem(const QString &item) {
    QComboBox::addItem(item);
    updateCompleterModel();
}

void ComboBox::addItems(const QStringList &items) {
    QComboBox::addItems(items);
    updateCompleterModel();
}

void ComboBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QComboBox::keyPressEvent(event);
        return;
    }

    QComboBox::keyPressEvent(event);

    QString text = currentText();
    completer->setCompletionPrefix(text);
    completer->complete();
}

void ComboBox::updateCompleterModel() {
    QStringList items;
    for (int i = 0; i < count(); ++i) {
        items << itemText(i);
    }
    QStringListModel *model = new QStringListModel(items, this);
    completer->setModel(model);
}
