#ifndef PRINTFORM_H
#define PRINTFORM_H

#include <QDialog>

#include <database/models/teacherplan.h>

class QPrinter;
class PrintTotalData;

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

private slots:
    void print();

    void on_btn_print_clicked();
    void on_btn_title_clicked();
    void on_btn_total_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::PrintForm *ui;

    QPrinter* setPrinter();
    void clearLayout(QLayout *layout);
    TeacherPlan *m_plan;
    User *m_user;
};

#endif // PRINTFORM_H
