#ifndef EDUCATIONROW_H
#define EDUCATIONROW_H

#include <QWidget>

namespace Ui {
class EducationRow;
}

class EducationRow : public QWidget
{
    Q_OBJECT

public:
    explicit EducationRow(QWidget *parent = nullptr);
    ~EducationRow();

private:
    Ui::EducationRow *ui;
};

#endif // EDUCATIONROW_H
