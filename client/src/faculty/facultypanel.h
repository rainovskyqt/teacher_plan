#ifndef FACULTYPANEL_H
#define FACULTYPANEL_H

#include <QTreeWidgetItem>
#include <QWidget>

#include <login/user.h>

namespace Ui {
class FacultyPanel;
}

class FacultyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FacultyPanel(QWidget *parent = nullptr);
    ~FacultyPanel();

    void setUser(User *newUser);

signals:
    void staffChanget(int);

private slots:
    void on_tree_plans_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::FacultyPanel *ui;

    User *m_user;
    int m_departmentId;

    bool personalPlanOnly();
    void setFaculty();
    void loadStaff();
};

#endif // FACULTYPANEL_H
