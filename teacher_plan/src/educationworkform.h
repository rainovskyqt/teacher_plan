#ifndef EDUCATIONWORKFORM_H
#define EDUCATIONWORKFORM_H

#include <QWidget>

namespace Ui {
class EducationWorkForm;
}

class EducationWorkForm : public QWidget
{
    Q_OBJECT

public:
    explicit EducationWorkForm(QWidget *parent = nullptr);
    ~EducationWorkForm();

private:
    Ui::EducationWorkForm *ui;
};

#endif // EDUCATIONWORKFORM_H
