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
    explicit GenerikWorkRow(GenericWork *work, QWidget *parent = nullptr);
    ~GenerikWorkRow();

    int planeHours();
    int factHours();
    QString toString();

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
};

#endif // GENERIKWORKROW_H
