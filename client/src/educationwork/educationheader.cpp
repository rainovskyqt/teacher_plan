#include "educationheader.h"
#include "ui_educationheader.h"

#include "QScrollBar"

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

void EducationHeader::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}
