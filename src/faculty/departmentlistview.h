#ifndef DEPARTMENTLISTVIEW_H
#define DEPARTMENTLISTVIEW_H

#include <QListView>
#include <QObject>

class DepartmentListView : public QListView
{
    Q_OBJECT
public:
    DepartmentListView(QWidget *parent = nullptr);

    void selectDepartment(int depId);
};

#endif // DEPARTMENTLISTVIEW_H
