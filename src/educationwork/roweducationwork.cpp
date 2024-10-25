#include "monthheader.h"
#include "roweducationwork.h"
#include "ui_roweducationwork.h"
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QScrollBar>

#include <misc/wheelblocker.hpp>
#include "database/dictionary/dictionarymanager.h"

#include <misc/months.h>

#define HEADER_HEIGHT 90
#define ROW_HEIGHT 54

RowEducationWork::RowEducationWork(int number, EducationWork *work, Position position, bool enabled, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RowEducationWork)
{
    ui->setupUi(this);

    setPosition(position, number, work);
    setEnabled(enabled);

    connect(ui->btn_up, &QPushButton::clicked, this, &RowEducationWork::rowUpClicked);
    connect(ui->btn_down, &QPushButton::clicked, this, &RowEducationWork::rowDownClicked);
    connect(ui->btn_add, &QPushButton::clicked, this, &RowEducationWork::addNewRow);
}

RowEducationWork::~RowEducationWork()
{
    delete ui;
}

QString RowEducationWork::toString() const
{
    return QString("%1(%2)").arg(
        ui->cb_discipline->currentText(),
        ui->cb_workForm->currentText()
        );
}

int RowEducationWork::id() const
{
    return m_work->id();
}

int RowEducationWork::row() const
{
    return m_row;
}

void RowEducationWork::setRow(int row)
{
    m_row = row;
    ui->lbl_rowNumber->setNum(m_row + 1);
}

EducationWork *RowEducationWork::work() const
{
    return m_work;
}

int RowEducationWork::sliderWight()
{
    return ui->scrollArea->horizontalScrollBar()->maximum();
}

void RowEducationWork::setHours(QHash<int, Hour*> hours)
{
    WeekEducationWork *weeks = this->findChildren<WeekEducationWork*>().at(0);          //Он всегда один
    if(weeks)
        weeks->setValues(hours);
}

void RowEducationWork::setSliderPosition(int pos)
{
    ui->scrollArea->horizontalScrollBar()->setValue(pos);
}

void RowEducationWork::setWidht(int widht)
{
    resize(widht, size().height());
}

void RowEducationWork::updateValues(int week)
{
    countTotal();

    emit valueChanged(m_work, week);
}

void RowEducationWork::resizeEvent(QResizeEvent *e)
{
    emit widhtChanged(this->size().width());
    QWidget::resizeEvent(e);
}

void RowEducationWork::setModels()
{
    setModel(DictionaryManager::get()->disciplines(), &m_disciplines, ui->cb_discipline);
    setModel(DictionaryManager::get()->courses(),&m_courses, ui->cb_course);
    setModel(DictionaryManager::get()->workForm(),&m_workForm, ui->cb_workForm);
}

void RowEducationWork::setModel(QAbstractItemModel *model, QSortFilterProxyModel *proxy, QComboBox *cbox)
{
    proxy->setSourceModel(model);
    cbox->setModel(proxy);
    cbox->setModelColumn(DictionaryModel::Name);
}

void RowEducationWork::setWorkData(EducationWork *work)
{
    m_work = work;

    setSaved(m_work->id());
    setComboboxData(&m_disciplines, ui->cb_discipline, work->disciplineId());
    setComboboxData(&m_courses, ui->cb_course, work->courseId());
    setComboboxData(&m_workForm, ui->cb_workForm, work->workFormId());
    ui->sb_groupCount->setValue(work->groupCount());
    ui->txt_comments->setPlainText(work->comments());
}

void RowEducationWork::setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex index = model->index(i, DictionaryModel::Id);
        if (model->data(index).toInt() == vId) {
            cbox->setCurrentIndex(index.row());
            return;
        }
    }
    cbox->setCurrentIndex(-1);
}

void RowEducationWork::setSaved(bool s)
{
    if(s)
        ui->lbl_rowNumber->setStyleSheet("background-color: rgb(100, 255, 100);");
    else
        ui->lbl_rowNumber->setStyleSheet("background-color: rgb(255, 100, 100);");
}

void RowEducationWork::setPosition(Position pos, int number, EducationWork *work)
{
    switch (pos) {
    case Position::Row:
        setAsRow(number, work);
        break;
    case Position::Header:
        setAsHeader();
        break;
    case Position::Footer:
        setAsFooter();
        break;
    }

    ui->sw_comboboxes->setCurrentIndex((int)pos);
    ui->sw_hourTypeLbl->setCurrentIndex((int)pos);
    ui->sw_comments->setCurrentIndex((int)pos);
    ui->sw_total->setCurrentIndex((int)pos);
}

void RowEducationWork::setAsRow(int number, EducationWork *work)
{
    ui->frame->setMaximumHeight(ROW_HEIGHT);
    ui->frame->setMinimumHeight(ROW_HEIGHT);

    WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});

    connect(ui->btn_delete, &QPushButton::clicked, this, &RowEducationWork::deleteWork);
    setRow(number);
    setModels();
    setWorkData(work);

    auto weeks = new WeekEducationWork(false, false, this);
    connect(weeks, &WeekEducationWork::valueChanged, this, &RowEducationWork::updateValues);
    weeks->setValues(work->hours());
    addWeeks(weeks);

    countTotal();
}

void RowEducationWork::addWeeks(QWidget *w)
{
    ui->hl_months->addWidget(w);
    ui->w_month->setMinimumWidth(ui->hl_months->sizeHint().width());
}

void RowEducationWork::setAsFooter()
{
    ui->frame->setMaximumHeight(ROW_HEIGHT);
    ui->frame->setMinimumHeight(ROW_HEIGHT);

    auto weekRow = new WeekEducationWork(true, true, this);
    addWeeks(weekRow);
}

void RowEducationWork::countTotal()
{
    int firstPlan = 0;
    int secondPlan = 0;
    int firstFact = 0;
    int secondFact = 0;

    auto m = Months::get();
    auto hours = m_work->hours();
    for(Hour *h : hours){
        if(m->isFirstSemester(h->week())){
            firstPlan += h->plan();
            firstFact += h->fact();
        } else {
            secondPlan += h->plan();
            secondFact += h->fact();
        }
    }
    ui->lbl_I_plan->setNum(firstPlan);
    ui->lbl_II_plan->setNum(secondPlan);
    ui->lbl_I_fact->setNum(firstFact);
    ui->lbl_II_fact->setNum(secondFact);
    ui->lbl_yearPlan->setNum(firstPlan + secondPlan);
    ui->lbl_yearFact->setNum(firstPlan + secondFact);
}

void RowEducationWork::setAsHeader()
{
    ui->frame->setMaximumHeight(HEADER_HEIGHT);
    ui->frame->setMinimumHeight(HEADER_HEIGHT);
    addWeeks(new MonthHeader(this));
}
