#ifndef FORMGENERIKWORK_H
#define FORMGENERIKWORK_H

#include <QListWidget>
#include <QWidget>
#include <database/models/teacherplan.h>
#include "database/models/datamodels.h"
#include "database/models/genericwork.h"
#include "genericfooter.h"

namespace Ui {
class FormGenerikWork;
}

class FormGenerikWork : public QWidget
{
    Q_OBJECT

public:
    explicit FormGenerikWork(QWidget *parent = nullptr);
    ~FormGenerikWork();

    WorkType type() const;
    void setType(WorkType newType);

public slots:
    void setPlanData(TeacherPlan *plan);

signals:
    void deleteWork();
    void clear();

private slots:
    void on_btn_add_clicked();
    void deleteRow();

private:
    Ui::FormGenerikWork *ui;

    WorkType m_type;
    TeacherPlan *m_plan;

    void setConnections();
    void addRow(GenericWork *work);
    QListWidget *currentList();
    QPair<int, int> countHours();
    GenericFooter *currentFooter();
    void fillTable();
    void clearData();

};

#endif // FORMGENERIKWORK_H
