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


private:
    Ui::GenerikWorkRow *ui;
    void loadWorks();
    GenericWork *m_work;
};

#endif // GENERIKWORKROW_H
