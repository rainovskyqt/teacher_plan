#include "educationrow.h"
#include "ui_educationrow.h"

#include "database/models/educationalwork.h"

EducationRow::EducationRow(int row, EducationalWork *work, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationRow)
{
    ui->setupUi(this);
    ui->lbl_number->setText(QString::number(row));
    setData(work);
}

EducationRow::~EducationRow()
{
    delete ui;
}

void EducationRow::setData(EducationalWork *work)
{
    ui->text_comments->setPlainText(work->comments());
}
