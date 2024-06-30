#ifndef EDUCATIONROW_H
#define EDUCATIONROW_H

#include <QWidget>

namespace Ui {
class EducationRow;
}

class EducationalWork;

class EducationRow : public QWidget
{
    Q_OBJECT

public:
    explicit EducationRow(int row, EducationalWork *work, QWidget *parent = nullptr);
    ~EducationRow();
    void setData(EducationalWork *work);

private:
    Ui::EducationRow *ui;
};

#endif // EDUCATIONROW_H
