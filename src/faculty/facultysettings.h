#ifndef FACULTYSETTINGS_H
#define FACULTYSETTINGS_H

#include <QDialog>
#include <staff/modelstafflist.h>

namespace Ui {
class FacultySettings;
}

class FacultySettings : public QDialog
{
    Q_OBJECT

public:
    explicit FacultySettings(QWidget *parent = nullptr);
    ~FacultySettings();

private slots:
    void on_lv_faculties_clicked(const QModelIndex &index);
    void changeYear(int yearId);
    void on_btn_add_clicked();
    void on_btn_edit_clicked();
    void on_btn_delete_clicked();

private:
    Ui::FacultySettings *ui;

    void init();
    void reloadList();
    void setBossVisible();
    void loadDepartments();
    void selectOwnDepartment();
    void selectDepartmentSettings(int depId, int yearId = 0);
    void initStaffModel();
    int getStaffId();

    ModelStaffList *m_staff;
};

#endif // FACULTYSETTINGS_H
