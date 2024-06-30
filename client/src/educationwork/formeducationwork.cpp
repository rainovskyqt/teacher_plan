#include "educationheader.h"
#include "educationrow.h"
#include "formeducationwork.h"
#include "ui_formeducationwork.h"
#include "database/models/educationalwork.h"
#include "database/database.h"
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

    auto eWork = Database::get()->educationWork(plan->baseId());
    foreach(auto work, eWork){
        addRow(work);
    }
}

void FormEducationWork::setTable()
{
    connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_edHeader, &EducationHeader::setPosition);
}

void FormEducationWork::addRow(EducationalWork *work)
{
    auto item = new QListWidgetItem(ui->lw_educationWork);
    auto row = new EducationRow(ui->lw_educationWork->count(), work);
    item->setSizeHint(row->sizeHint());
    ui->lw_educationWork->setItemWidget(item, row);
}

void FormEducationWork::on_btn_add_clicked()
{
    auto work = new EducationalWork();
    m_plan->addEducationaWork(work);
    addRow(work);
}

