#ifndef GENERIKWORKROW_H
#define GENERIKWORKROW_H

#include <QWidget>
#include <database/models/genericwork.h>

namespace Ui {
class GenerikWorkRow;
}

class GenerikWorkRow : public QWidget
{
    Q_OBJECT

public:
    explicit GenerikWorkRow(GenericWork *work, int number, QWidget *parent = nullptr);
    ~GenerikWorkRow();

    int position() const;
    QString workName();
    int planeHours() const;
    int factHours() const;
    const QString toString() const;
    const QString comments() const;

    GenericWork *work() const;

    void init();

signals:
    void valueChanged();
    void deleteWork();

private:
    Ui::GenerikWorkRow *ui;
    GenericWork *m_work;

    void loadWorkTypes();
    void setWorkData(GenericWork *work);
    void makeConnections();

    void colorRow(bool accepted);

};

#endif // GENERIKWORKROW_H
