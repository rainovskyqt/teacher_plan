#include "educationworkform.h"
#include "ui_educationworkform.h"

EducationWorkForm::EducationWorkForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EducationWorkForm)
{
    ui->setupUi(this);
}

EducationWorkForm::~EducationWorkForm()
{
    delete ui;
}
