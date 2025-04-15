#include "formgenerikwork.h"
#include "ui_formgenerikwork.h"

#include <QMessageBox>
#include <QScrollBar>

#include <database/models/genericwork.h>
#include "generic/generikworkrow.h"

#include <database/database.h>

#include <print/datafiles/printgenericdata.h>

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

    fillTable();
}

void FormGenerikWork::setGenericTime(PrintGenericData *c)
{
    auto list = c->isSecond() ? ui->lw_second : ui->lw_first;
    auto rows = list->findChildren<GenerikWorkRow*>();
    for(auto r: rows){
        c->addWork(r->position(),new PrintGenericWork(r->position(),
                                                       r->workName(),
                                                       r->planeHours(),
                                                       r->factHours(),
                                                       r->comments())
                   );
    }
}

void FormGenerikWork::addRow(GenericWork *work)
{
    auto list = work->semester() == 1 ? ui->lw_first : ui->lw_second;
    auto item = new QListWidgetItem(list);

    work->setOrderPlace(list->count());

    auto row = new GenerikWorkRow(work, list->count());

    item->setSizeHint(row->sizeHint());
    list->setItemWidget(item, row);

    connect(row, &GenerikWorkRow::deleteWork, this, &FormGenerikWork::deleteRow);
    Database::get()->saveWork(work);

    connect(row, &GenerikWorkRow::valueChanged, this, [=]{
        auto hours = countHours(work->semester() == 1 ? ui->lw_first : ui->lw_second);
        auto footer = work->semester() == 1 ? ui->w_footerFirst : ui->w_footerSecond;
        footer->setValues(hours.first, hours.second);

        emit planValueChanged(work->workType(), static_cast<PlanTime::Semester>(work->semester()), hours.first);    //hours.first - планируемое время
    });

    row->init();
}

QListWidget *FormGenerikWork::currentList()
{
    if(isFirstSemester())
        return ui->lw_first;
    else
        return ui->lw_second;
}

QPair<int, int> FormGenerikWork::countHours(QWidget *list)
{
    int planCount = 0;
    int factCount = 0;
    auto rows = list->findChildren<GenerikWorkRow*>();
    for(auto r: rows){
        planCount += r->planeHours();
        factCount += r->factHours();
    }
    return qMakePair(planCount, factCount);
}

GenericFooter *FormGenerikWork::currentFooter()
{
    if(isFirstSemester())
        return ui->w_footerFirst;
    else
        return ui->w_footerSecond;
}

void FormGenerikWork::clearAllData()
{
    clearData(ui->lw_first);
    clearData(ui->lw_second);
    emit clear();
}

void FormGenerikWork::fillTable()
{
    clearAllData();

    auto eWork = Database::get()->genericWork(m_plan->baseId(), m_type);
    for(auto work: eWork){
        addRow(work);
    }
}

void FormGenerikWork::clearData(QListWidget *list)
{
    auto rows = list->findChildren<GenerikWorkRow*>();
    qDeleteAll(rows.begin(), rows.end());
    list->clear();

    emit clear();
}

void FormGenerikWork::on_btn_add_clicked()
{
    auto work = new GenericWork(m_type, m_plan->baseId());
    work->setSemester(isFirstSemester() ? 1 : 2);
    addRow(work);
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
    emit planValueChanged(workRow->work()->workType(), PlanTime::FirstSemester , 0);
    emit planValueChanged(workRow->work()->workType(), PlanTime::SecondSemestr , 0);
}

int FormGenerikWork::currentSemester()
{
    if(ui->tabWidget->currentIndex() == 0)
        return First;
    else
        return Second;
}

bool FormGenerikWork::isFirstSemester()
{
    return currentSemester() == First;
}

