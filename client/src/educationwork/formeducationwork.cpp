#include "educationheader.h"
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

void FormEducationWork::setPlanData(TeacherPlan *plan)
{
}

void FormEducationWork::setTable()
{
    auto item = new QListWidgetItem();
    auto header = new EducationHeader();
    ui->lw_educationWork->addItem(item);
    item->setSizeHint(header->sizeHint());
    ui->lw_educationWork->setItemWidget(item, header);
}
