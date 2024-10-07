#ifndef HEADERCOMBOBOX_H
#define HEADERCOMBOBOX_H

#include <QComboBox>
#include <QEvent>
#include <QObject>
#include <QWheelEvent>
#include <QWidget>

class HeaderComboBox : public QComboBox
{
public:
    HeaderComboBox(QWidget *parent);
};

#endif // HEADERCOMBOBOX_H
