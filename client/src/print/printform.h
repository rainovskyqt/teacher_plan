#ifndef PRINTFORM_H
#define PRINTFORM_H

#include <QDialog>
#include <QPrinter>

#include <database/models/teacherplan.h>

#include <print/datafiles/printcomplite.h>
#include <print/datafiles/printgenericdata.h>

class PrintTotalData;
class PrintStudyData;

namespace Ui {
class PrintForm;
}

class PrintForm : public QDialog
{
    Q_OBJECT

public:
    explicit PrintForm(TeacherPlan *plan, User *user, QWidget *parent = nullptr);
    ~PrintForm();

signals:
    void getTotalTime(PrintTotalData *d);
    void getCompliteTime(PrintComplite *d);
    void getGenericTime(WorkType, PrintGenericData *d);
    void getStudyTime(PrintStudyData *d);

private slots:
    void print();

    void on_btn_print_clicked();
    void on_btn_title_clicked();
    void on_btn_total_clicked();
    void on_btn_cancel_clicked();
    void on_btn_analisis_clicked();
    void on_rb_first_clicked();
    void on_rb_second_clicked();
    void on_btn_complete_clicked();
    void on_btn_workMethodic_clicked();
    void on_btn_researchingWork_clicked();
    void on_btn_sportWork_clicked();
    void on_btn_otherWork_clicked();
    void on_btn_workStudy_clicked();

private:
    Ui::PrintForm *ui;

    TeacherPlan *m_plan;
    User *m_user;

    QPrinter::Orientation getOrientation();
    QPrinter* setPrinter(QPrinter::Orientation o);
    void clearLayout(QLayout *layout);
    void setSemester();
};

#endif // PRINTFORM_H
