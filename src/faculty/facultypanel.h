#ifndef FACULTYPANEL_H
#define FACULTYPANEL_H

#include <QTreeWidgetItem>
#include <QWidget>

#include <staff/modelyear.h>

#include "modelfaculty.h"

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
    void loadTechers(int index);

private:
    Ui::FacultyPanel *ui;

    ModelFaculty m_model;
    ModelYear m_modelYear;

    bool personalPlanOnly();
    void setYearModel();
    void setUserData(User *user);
    void setModel();
};

#endif // FACULTYPANEL_H
