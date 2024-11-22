#ifndef GENERIKWORKROW_H
#define GENERIKWORKROW_H

#include "genericwork.h"

#include <QComboBox>
#include <QSortFilterProxyModel>
#include <QWidget>

namespace Ui {
class GenerikWorkRow;
}

class GenerikWorkRow : public QWidget
{
    Q_OBJECT

public:
    explicit GenerikWorkRow(GenericWork *work, int number, QWidget *parent = nullptr);
    ~GenerikWorkRow();

    // int planeHours();
    // int factHours();
    QString toString();

    // GenericWork *work() const;

    // void init();

signals:
    void valueChanged();
    void saveWork(GenericWork *work);
    void deleteWork();

private:
    Ui::GenerikWorkRow *ui;

    QSortFilterProxyModel m_workForms;

    GenericWork *m_work;

    void setWorkData(GenericWork *work);
    void setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId);

    void colorRow(bool accepted);

};

#endif // GENERIKWORKROW_H
