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

    connect(ui->w_footer, &EducationalFooter::firstPlaneChanget, this, &FormEducationWork::firstPlaneChanget);
    connect(ui->w_footer, &EducationalFooter::secondPlaneChanget, this, &FormEducationWork::secondPlaneChanget);
    connect(ui->w_footer, &EducationalFooter::firstFacticalChanget, this, &FormEducationWork::firstFacticalChanget);
    connect(ui->w_footer, &EducationalFooter::secondFacticalChanget, this, &FormEducationWork::secondFacticalChanget);
}

void FormEducationWork::fillTable()
{
    ui->lw_educationWork->clear();

    auto eWork = Database::get()->educationWork(m_plan->baseId());
    foreach(auto work, eWork){
        addRow(work);
    }

    countAllValues();
}

void FormEducationWork::addRow(EducationalWork *work)
{
    auto item = new QListWidgetItem(ui->lw_educationWork);
    auto row = new EducationRow(ui->lw_educationWork->count(), work);
    item->setSizeHint(row->sizeHint());
    ui->lw_educationWork->setItemWidget(item, row);
    connect(row, &EducationRow::deleteWork, this, &FormEducationWork::deleteRow);
    Database::get()->saveWork(work);

    connect(row, &EducationRow::valueChanget, this, [this](QString line){
        ui->w_footer->setValue(countHours(line), line);
    });

    connect(row, &EducationRow::totalValueChanget, this, [this](QString lbl){
        ui->w_footer->setTotalValue(countTotalHours(lbl), lbl);
    });
}

int FormEducationWork::countHours(QString name)
{
    int count = 0;
    for(int i = 0; i < ui->lw_educationWork->count(); ++i){
        EducationRow *row = dynamic_cast<EducationRow*>(ui->lw_educationWork->itemWidget(
            ui->lw_educationWork->item(i)));
        count += row->getValue(name);
    }
    return count;
}

int FormEducationWork::countTotalHours(QString name)
{
    int count = 0;
    for(int i = 0; i < ui->lw_educationWork->count(); ++i){
        EducationRow *row = dynamic_cast<EducationRow*>(ui->lw_educationWork->itemWidget(
            ui->lw_educationWork->item(i)));
        count += row->getTotalValue(name);
    }
    return count;
}

void FormEducationWork::countAllValues()
{
    auto hours = ui->w_footer->hourFields();
    foreach(auto h, hours)
        ui->w_footer->setValue(countHours(h), h);

    auto totals = ui->w_footer->totalFields();
    foreach(auto t, totals)
        ui->w_footer->setTotalValue(countTotalHours(t), t);
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

