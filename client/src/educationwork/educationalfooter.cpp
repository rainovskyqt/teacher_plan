#include "educationalfooter.h"
#include "ui_educationalfooter.h"
#include <QScrollBar>

EducationalFooter::EducationalFooter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EducationalFooter)
{
    ui->setupUi(this);
}

EducationalFooter::~EducationalFooter()
{
    delete ui;
}

void EducationalFooter::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}
