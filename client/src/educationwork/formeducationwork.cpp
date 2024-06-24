#include "formeducationwork.h"
#include "ui_formeducationwork.h"

#include <misc/HierarchicalHeaderView.h>

FormEducationWork::FormEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormEducationWork)
{
    ui->setupUi(this);
    setTable();
}

FormEducationWork::~FormEducationWork()
{
    delete ui;
}

void FormEducationWork::setTable()
{
    ui->tv_educationWork->setHorizontalHeader(new HierarchicalHeaderView(Qt::Horizontal, ui->tv_educationWork));
}
