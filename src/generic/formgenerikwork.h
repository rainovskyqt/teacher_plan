#ifndef FORMGENERIKWORK_H
#define FORMGENERIKWORK_H

#include <QListWidget>
#include <QWidget>

#include "database/types.h"
#include "genericfooter.h"
#include "genericwork.h"

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
    void setPlan(int planId);

signals:
    // void deleteWork();
    // void clear();
    // void planValueChanged(WorkType, PlanTime::Semester, int);

private slots:
    void on_btn_add_clicked();
    // void deleteRow();

private:
    Ui::FormGenerikWork *ui;

    enum Semester{
        First,
        Second
    };

    WorkType m_type;
    int m_planId;

    void addRow(GenericWork *work);
    int currentSemester();
    bool isFirstSemester();

    // QListWidget *currentList();
    // QPair<int, int> countHours(QWidget *list);
    // GenericFooter *currentFooter();
    // void clearAllData();
    // void clearData(QListWidget *list);
    // void fillTable();

};

#endif // FORMGENERIKWORK_H
