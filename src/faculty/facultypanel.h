#ifndef FACULTYPANEL_H
#define FACULTYPANEL_H

#include <QTreeWidgetItem>
#include <QWidget>

#include "modelstafflist.h"

class User;

namespace Ui {
class FacultyPanel;
}

class FacultyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FacultyPanel(QWidget *parent = nullptr);
    ~FacultyPanel();

    void init();
    bool canBeVisible();


signals:
    void staffChanged(int);

private slots:
    void setOwnPlans();

private:
    Ui::FacultyPanel *ui;

    ModelStaffList model;

    bool personalPlanOnly();
    void setUserData(User *user);
    void setModel(User *user);
};

#endif // FACULTYPANEL_H
