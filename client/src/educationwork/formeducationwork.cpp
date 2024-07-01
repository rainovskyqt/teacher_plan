#include "educationheader.h"
#include "educationrow.h"
#include "formeducationwork.h"
#include "ui_formeducationwork.h"
#include "database/models/educationalwork.h"
#include "database/database.h"
#include <QScrollBar>
#include <QMessageBox>

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
    m_plan = plan;
    fillTable();
}

void FormEducationWork::setTable()
{
    connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_edHeader, &EducationHeader::setPosition);
    connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_footer, &EducationalFooter::setPosition);
}

void FormEducationWork::fillTable()
{
    ui->lw_educationWork->clear();

    auto eWork = Database::get()->educationWork(m_plan->baseId());
    foreach(auto work, eWork){
        addRow(work);
    }
}

void FormEducationWork::addRow(EducationalWork *work)
{
    auto item = new QListWidgetItem(ui->lw_educationWork);
    auto row = new EducationRow(ui->lw_educationWork->count(), work);
    item->setSizeHint(row->sizeHint());
    ui->lw_educationWork->setItemWidget(item, row);
    connect(row, &EducationRow::deleteWork, this, &FormEducationWork::deleteRow);
    Database::get()->saveWork(work);

    connect(row, &EducationRow::valueChanget, this, [this]{
        auto list = ui->lw_educationWork->item
    });
}

void FormEducationWork::on_btn_add_clicked()
{
    auto work = new EducationalWork(m_plan->baseId());
    m_plan->addEducationaWork(work);
    addRow(work);
}

void FormEducationWork::deleteRow()
{
    auto workRow = dynamic_cast<EducationRow*>(sender());
    if(QMessageBox::question(this,
                              "Удаление",
                              QString("Удалить %1 из списка?").arg(workRow->toString()))
        == QMessageBox::No)
        return;
    Database::get()->deleteWork(workRow->work());
    fillTable();
}

