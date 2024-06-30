#include "educationrow.h"
#include "ui_educationrow.h"

EducationRow::EducationRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationRow)
{
    ui->setupUi(this);
}

EducationRow::~EducationRow()
{
    delete ui;
}
