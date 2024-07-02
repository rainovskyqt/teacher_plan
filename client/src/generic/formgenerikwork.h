#ifndef FORMGENERIKWORK_H
#define FORMGENERIKWORK_H

#include <QListWidget>
#include <QWidget>
#include "database/models/datamodels.h"
#include "database/models/genericwork.h"

namespace Ui {
class FormGenerikWork;
}

class FormGenerikWork : public QWidget
{
    Q_OBJECT

public:
    explicit FormGenerikWork(QWidget *parent = nullptr);
    ~FormGenerikWork();

private slots:
    void on_btn_add_clicked();

private:
    Ui::FormGenerikWork *ui;
    void setConnections();
    WorkType m_type;
    void addRow(GenericWork *work);
    QListWidget *currentList();
};

#endif // FORMGENERIKWORK_H
