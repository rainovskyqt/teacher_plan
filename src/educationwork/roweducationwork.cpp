#include "montheducationwork.h"
#include "monthheader.h"
#include "roweducationwork.h"
#include "ui_roweducationwork.h"
#include "weekeducationwork.h"

#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QScrollBar>

#include <misc/wheelblocker.hpp>
#include "database/dictionary/dictionarymanager.h"

#include <misc/months.h>

#define HEADER_HEIGHT 90
#define ROW_HEIGHT 54

RowEducationWork::RowEducationWork(int number, const ModelEducationWork::EducationWork &work,
                                   Position position, bool enabled, QWidget *parent)
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
    return m_work.id;
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

ModelEducationWork::EducationWork RowEducationWork::work() const
{
    return m_work;
}

int RowEducationWork::sliderWight()
{
    return ui->scrollArea->horizontalScrollBar()->maximum();
}

void RowEducationWork::setSliderPosition(int pos)
{
    ui->scrollArea->horizontalScrollBar()->setValue(pos);
}

void RowEducationWork::setWidht(int widht)
{
    resize(widht, size().height());
}

void RowEducationWork::updateValues(ModelEducationWork::Hour hour)
{
    m_work.hours.insert(hour.week, hour);
    countValues();
    emit valueChanged(hour);
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

void RowEducationWork::setWorkData(const ModelEducationWork::EducationWork &work)
{
    m_work = work;

    setSaved(m_work.id);
    setComboboxData(&m_disciplines, ui->cb_discipline, work.disciplineId);
    setComboboxData(&m_courses, ui->cb_course, work.courseId);
    setComboboxData(&m_workForm, ui->cb_workForm, work.workFormId);
    ui->sb_groupCount->setValue(work.groupCount);    
    ui->txt_comments->setPlainText(work.comments);
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

void RowEducationWork::setPosition(Position pos, int number, const ModelEducationWork::EducationWork &work)
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

void RowEducationWork::setAsRow(int number, const ModelEducationWork::EducationWork &work)
{
    ui->frame->setMaximumHeight(ROW_HEIGHT);
    ui->frame->setMinimumHeight(ROW_HEIGHT);

    WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});

    connect(ui->btn_delete, &QPushButton::clicked, this, &RowEducationWork::deleteWork);
    setRow(number);
    setModels();
    setWorkData(work);

    // auto weeks = work.hours;
    // for(int i = 1; i < ){
    auto newM = new WeekEducationWork({}, this);
        // connect(newM, &MonthEducationWork::valueChanged, this, &RowEducationWork::updateValues);
        addMonth(newM);
        // addMonth();
    // }

    // countValues();
}

void RowEducationWork::addMonth(QWidget *w)
{
    int h = ui->hl_months->sizeHint().width();
    ui->hl_months->addWidget(w);
    int k = ui->hl_months->sizeHint().width();
    ui->w_month->setMinimumWidth(ui->hl_months->sizeHint().width());
}

void RowEducationWork::setAsFooter()
{
    ui->frame->setMaximumHeight(ROW_HEIGHT);
    ui->frame->setMinimumHeight(ROW_HEIGHT);

    // auto months = Months::get()->educationYearList();
    // for(auto m : months){
    //     addMonth(new MonthEducationWork(this, m));
    // }
}

void RowEducationWork::countValues()
{
    int planeCountI = 0;
    int  planeCountII = 0;
    int factCountI = 0;
    int factCountII = 0;

    auto hours = m_work.hours.values();
    for(auto h : hours){

        if(Months::get()->isFirstSemester(h.week)){
            planeCountI += h.planValue;
            factCountI += h.factValue;
        } else {
            planeCountII += h.planValue;
            factCountII += h.factValue;
        }
    }

    ui->lbl_I_plan->setNum(planeCountI);
    ui->lbl_II_plan->setNum(planeCountII);
    ui->lbl_I_fact->setNum(factCountI);
    ui->lbl_II_fact->setNum(factCountII);

    ui->lbl_yearPlan->setNum(planeCountI + planeCountII);
    ui->lbl_yearFact->setNum(factCountI + factCountII);
}

void RowEducationWork::setAsHeader()
{
    ui->frame->setMaximumHeight(HEADER_HEIGHT);
    ui->frame->setMinimumHeight(HEADER_HEIGHT);
    addMonth(new MonthHeader(this));
}
