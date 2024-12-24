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

    connect(ui->w_footer, &EducationalFooter::firstPlaneChanged, this, [&](int val){
        emit planValueChanged(WorkType::Educational, PlanTime::FirstSemester, val);
    });
    connect(ui->w_footer, &EducationalFooter::secondPlaneChanged, this, [&](int val){
        emit planValueChanged(WorkType::Educational, PlanTime::SecondSemestr, val);
    });

    ui->scrolbar->setMaximum(ui->w_edHeader->timeAreaWidth());
}

void FormEducationWork::fillTable()
{
    clearData();

    auto works = Database::get()->educationWork(m_plan->baseId());
    for(auto work: works){
        addRow(work);
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

    connect(row, &EducationRow::factValueChanged, this, &FormEducationWork::countFactValue);
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

void FormEducationWork::updateRowNumber(int start)
{
    for(int i = start; i < ui->lw_educationWork->count(); ++i){
        auto row = dynamic_cast<EducationRow*>(ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(i)));
        row->setRow(i + 1);
    }
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

    int row = workRow->row() - 1;

    delete ui->lw_educationWork->item(row);
    updateRowNumber(row);
}

void FormEducationWork::countFactValue(Month::Months month, int workType, int, EducationalHour::HourType hourType)
{
    int count = 0;
    auto rows = this->findChildren<EducationRow*>();
    for(auto r: rows){
        if(r->workForm() == workType){
            count += r->countMonthHourse(month, hourType);
        }
    }
    emit monthValueChanged(month, workType, count, hourType);
    // if(hourType == EducationalHour::HourType::Factical)
        // emit factValueChanged(month, workType, count);
    // else
    //     emit planMaonthValueChanged(month, workType, count);
}

void FormEducationWork::clearData()
{
    ui->lw_educationWork->clear();
    ui->w_footer->clear();
    auto rows = this->findChildren<EducationRow*>();
    qDeleteAll(rows.begin(), rows.end());
    emit clear();
}

