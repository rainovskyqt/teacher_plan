#ifndef YEARCOMBOBOX_H
#define YEARCOMBOBOX_H

#include <QComboBox>
#include <QObject>

class YearCombobox : public QComboBox
{
    Q_OBJECT
public:
    YearCombobox(QWidget *parent = nullptr);

    int selectedYear();

signals:
    void yearChanged(int);

private:
    void init();

    void setCurrentYear();
};

#endif // YEARCOMBOBOX_H
