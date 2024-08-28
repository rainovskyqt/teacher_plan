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
//    connect(ui->w_footer, &EducationalFooter::firstFacticalChanget, this, &FormEducationWork::firstFacticalChanget);
//    connect(ui->w_footer, &EducationalFooter::secondFacticalChanget, this, &FormEducationWork::secondFacticalChanget);
}

void FormEducationWork::fillTable()
{
    clearData();

    auto eWork = Database::get()->educationWork(m_plan->baseId());
    for(auto work: eWork){
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
    connect(row, &EducationRow::valueChanget, this, [this](EducationalHour *hour){
        auto h = new EducationalHour(-1, -1, hour->week(), countHours(hour->type(), hour->week()),
                                     hour->type(), ui->w_footer);
        ui->w_footer->setValue(h);
    });

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

