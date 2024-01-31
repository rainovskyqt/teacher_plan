#include "formeducationwork.h"
#include "ui_formeducationwork.h"

FormEducationWork::FormEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormEducationWork)
{
    ui->setupUi(this);
}

FormEducationWork::~FormEducationWork()
{
    delete ui;
}
