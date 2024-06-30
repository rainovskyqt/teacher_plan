#include "educationheader.h"
#include "educationrow.h"
#include "formeducationwork.h"
#include "ui_formeducationwork.h"

#include <QScrollBar>

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
    ui->lw_educationWork->clear();
    for(auto i = 0; i < 15; ++i){
    auto item = new QListWidgetItem(ui->lw_educationWork);
    auto row = new EducationRow();
    item->setSizeHint(row->sizeHint());
    ui->lw_educationWork->setItemWidget(item, row);
    }
}

void FormEducationWork::setTable()
{
//    ui->lw_educationWork->resize(ui->w_header->width(), ui->lw_educationWork->height());
    connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_edHeader, &EducationHeader::setPosition);
}
