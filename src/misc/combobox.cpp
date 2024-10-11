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

void ComboBox::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOptionComboBox opt;
    initStyleOption(&opt);
    style()->drawComplexControl(QStyle::CC_ComboBox, &opt, &painter, this);

    QString text = currentText();
    QRect textRect = opt.rect.adjusted(5, 0, -20, 0);
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    textOption.setAlignment(Qt::AlignHCenter);

    QFontMetrics metrics(font());
    QRect boundingRect = metrics.boundingRect(textRect, Qt::TextWordWrap, text);
    boundingRect.setWidth(textRect.width());
    painter.drawText(textRect, Qt::TextWordWrap, text);
}

QSize ComboBox::minimumSizeHint() const {
    QSize size = QComboBox::minimumSizeHint();
    QFontMetrics metrics(font());
    QString text = currentText();

    int textHeight = metrics.boundingRect(QRect(0, 0, width() - 10, 0), Qt::TextWordWrap, text).height();
    size.setHeight(textHeight + 10);

    return size;
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
