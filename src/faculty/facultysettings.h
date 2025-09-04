#ifndef FACULTYSETTINGS_H
#define FACULTYSETTINGS_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class FacultySettings;
}

class FacultySettings : public QDialog
{
    Q_OBJECT

public:
    explicit FacultySettings(QWidget *parent = nullptr);
    ~FacultySettings();

private:
    Ui::FacultySettings *ui;

    void init();
    void setBossVisible();
    void loadDepartments();

    QSqlQueryModel *m_departments;
};

#endif // FACULTYSETTINGS_H
