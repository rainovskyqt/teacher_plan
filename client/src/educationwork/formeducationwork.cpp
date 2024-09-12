#include "educationheader.h"
#include "educationrow.h"
#include "formeducationwork.h"
#include "ui_formeducationwork.h"
#include "database/models/educationalwork.h"
#include "database/database.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QListWidgetItem>

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
    connect(ui->scrolbar, &QScrollBar::valueChanged, ui->w_edHeader, &EducationHeader::setPosition);
    connect(ui->scrolbar, &QScrollBar::valueChanged, ui->w_footer, &EducationalFooter::setPosition);

    // connect(ui->scrolbar, &QScrollBar::valueChanged, ui->w_edHeader, &EducationHeader::setScrolBarValue);

    connect(ui->w_footer, &EducationalFooter::firstPlaneChanged, this, &FormEducationWork::firstPlaneChanged);
    connect(ui->w_footer, &EducationalFooter::secondPlaneChanged, this, &FormEducationWork::secondPlaneChanged);

}

void FormEducationWork::fillTable()
{
    clearData();

    auto eWork = Database::get()->educationWork(m_plan->baseId());
    for(auto work: eWork){
        addRow(work);
    }
    auto timeAreaWidth = dynamic_cast<EducationRow*>(ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(0)));
    if(timeAreaWidth){
        ui->scrolbar->setMaximum(timeAreaWidth->timeAreaWidth());
    }
}

void FormEducationWork::addRow(EducationalWork *work)
{
    auto item = new QListWidgetItem(ui->lw_educationWork);

    work->setOrderPlace(ui->lw_educationWork->count());

    auto row = new EducationRow(ui->lw_educationWork->count(), work);
    item->setSizeHint(row->sizeHint());
    ui->lw_educationWork->setItemWidget(item, row);

    connect(row, &EducationRow::deleteWork, this, &FormEducationWork::deleteRow);
    connect(row, &EducationRow::valueChanged, this, [this](EducationalHour *hour){
        auto h = new EducationalHour(-1, -1, hour->week(), countHours(hour->type(), hour->week()),
                                     hour->type(), ui->w_footer);
        ui->w_footer->setValue(h);
    });

    connect(row, &EducationRow::factValueChanged, this, &FormEducationWork::factValueChanged);
    connect(ui->scrolbar, &QScrollBar::valueChanged, row, &EducationRow::setScrolBarValue);

    row->loadHours();           //Часы устанасливаются после подключения сигнала к футеру, что бы сработал посчет часов
}

int FormEducationWork::countHours(EducationalHour::HourType type, int week)
{
    int count = 0;
    auto month = this->findChildren<EducationRow*>();
    for(auto m: month){
        count += m->getTime(type, week);
    }
    return count;
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

void FormEducationWork::clearData()
{
    ui->lw_educationWork->clear();
    ui->w_footer->clear();
    emit clear();
}

