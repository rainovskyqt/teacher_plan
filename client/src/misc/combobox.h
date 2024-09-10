#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QCompleter>
#include <QKeyEvent>
#include <QObject>

class ComboBox : public QComboBox
{
public:
    ComboBox(QWidget *parent = nullptr);
    void addItem(const QString &item);
    void addItems(const QStringList &items);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QCompleter *completer;

    void updateCompleterModel();
};

#endif // COMBOBOX_H
