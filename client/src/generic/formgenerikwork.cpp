#include "formgenerikwork.h"
#include "ui_formgenerikwork.h"

#include <QMessageBox>
#include <QScrollBar>

#include <database/models/genericwork.h>
#include "generic/generikworkrow.h"

#include <database/database.h>

FormGenerikWork::FormGenerikWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormGenerikWork)
{
    ui->setupUi(this);
    setConnections();
}

FormGenerikWork::~FormGenerikWork()
{
    delete ui;
}

void FormGenerikWork::setConnections()
{
    // connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
    //         ui->w_edHeader, &EducationHeader::setPosition);

    connect(ui->lw_first->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_footerFirst, &GenericFooter::setPosition);
    connect(ui->lw_second->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_footerSecond, &GenericFooter::setPosition);
}

WorkType FormGenerikWork::type() const
{
    return m_type;
}

void FormGenerikWork::setType(WorkType newType)
{
    m_type = newType;
}

void FormGenerikWork::setPlanData(TeacherPlan *plan)
{
    m_plan = plan;
}

void FormGenerikWork::addRow(GenericWork *work)
{
    auto list = currentList();
    auto item = new QListWidgetItem(list);
    auto row = new GenerikWorkRow(work);
    item->setSizeHint(row->sizeHint());
    list->setItemWidget(item, row);

    connect(row, &GenerikWorkRow::deleteWork, this, &FormGenerikWork::deleteRow);
    Database::get()->saveWork(work);

    connect(row, &GenerikWorkRow::valueChanged, this, [&]{
        auto hours = countHours();
        auto footer = currentFooter();
        footer->setValues(hours.first, hours.second);
    });
}

QListWidget *FormGenerikWork::currentList()
{
    if(ui->tabWidget->currentIndex() == 0)
        return ui->lw_first;
    else
        return ui->lw_second;
}

QPair<int, int> FormGenerikWork::countHours()
{
    int planCount = 0;
    int factCount = 0;
    auto rows = this->findChildren<GenerikWorkRow*>();
    for(auto r: rows){
        planCount += r->planeHours();
        factCount += r->factHours();
    }
    return qMakePair(planCount, factCount);
}

GenericFooter *FormGenerikWork::currentFooter()
{
    if(ui->tabWidget->currentIndex() == 0)
        return ui->w_footerFirst;
    else
        return ui->w_footerSecond;
}

void FormGenerikWork::fillTable()
{
    clearData();

    auto eWork = Database::get()->genericWork(m_plan->baseId());
    for(auto work: eWork){
        addRow(work);
    }
}

void FormGenerikWork::clearData()
{
    auto list = currentList();
    list->clear();
    emit clear();
}

void FormGenerikWork::on_btn_add_clicked()
{
    addRow(new GenericWork(m_type, m_plan->baseId()));
}

void FormGenerikWork::deleteRow()
{
    auto workRow = dynamic_cast<GenerikWorkRow*>(sender());
    if(QMessageBox::question(this,
                              "Удаление",
                              QString("Удалить %1 из списка?").arg(workRow->toString()))
        == QMessageBox::No)
        return;
    Database::get()->deleteWork(workRow->work());
    fillTable();
}

