#include "educationheader.h"
#include "ui_educationheader.h"

EducationHeader::EducationHeader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationHeader)
{
    ui->setupUi(this);
}

EducationHeader::~EducationHeader()
{
    delete ui;
}
