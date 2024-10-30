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

RowEducationWork::RowEducationWork(int number, Position position, bool readOnly, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RowEducationWork)
    , m_workType(WorkType::Educational)
    , m_work(nullptr)
{
    ui->setupUi(this);

    setReadOnly(readOnly);
    setPosition(position, number);

    connect(ui->btn_up, &QPushButton::clicked, this, &RowEducationWork::rowUpClicked);
    connect(ui->btn_down, &QPushButton::clicked, this, &RowEducationWork::rowDownClicked);
    connect(ui->btn_add, &QPushButton::clicked, this, &RowEducationWork::addNewRow);

    makeConnects();
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
    int orderPlace = m_row + 1;
    ui->lbl_rowNumber->setNum(orderPlace);
    if(m_work && m_work->orderPlace() != orderPlace){
        m_work->setOrderPlace(orderPlace);
        emit saveWork(m_work);
    }
}

EducationWork *RowEducationWork::work() const
{
    return m_work;
}

int RowEducationWork::sliderWight()
{
    return ui->scrollArea->horizontalScrollBar()->maximum();
}

void RowEducationWork::setHours(QMap<int, Hour*> hours)
{
    WeekEducationWork *weeks = this->findChild<WeekEducationWork*>();
    if(weeks){
        weeks->setValues(hours);
        m_totalHours.setHours(hours);
    }
    setTotal();
}

void RowEducationWork::setSliderPosition(int pos)
{
    ui->scrollArea->horizontalScrollBar()->setValue(pos);
}

void RowEducationWork::setWidht(int widht)
{
    resize(widht, size().height());
}

void RowEducationWork::setReadOnly(bool read)
{
    m_readOnly = read;
    auto btns = this->findChildren<QAbstractButton*>();
    for(auto b : btns)
        b->setEnabled(!read);

    auto boxes = this->findChildren<QComboBox*>();
    for(auto b : boxes)
        b->setEnabled(!read);

    auto sboxes = this->findChildren<QSpinBox*>();
    for(auto b : sboxes)
        b->setEnabled(!read);
}

void RowEducationWork::updateValues(int week)
{
    setTotal();
    emit sliderMaximum(sliderWight());
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
    makeDisconnects();
    m_work = work;

    setSaved(m_work->id());
    setComboboxData(&m_disciplines, ui->cb_discipline, work->disciplineId());
    setComboboxData(&m_courses, ui->cb_course, work->courseId());
    setComboboxData(&m_workForm, ui->cb_workForm, work->workFormId());
    ui->sb_groupCount->setValue(work->groupCount());
    ui->txt_comments->setPlainText(work->comments());

    auto weeks = new WeekEducationWork(m_readOnly, m_readOnly, this);
    connect(weeks, &WeekEducationWork::valueChanged, this, &RowEducationWork::updateValues);
    setHours(work->hours());
    addWeeks(weeks);
    makeConnects();
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

void RowEducationWork::setPosition(Position pos, int number)
{
    switch (pos) {
    case Position::Row:
        setAsRow(number);
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

void RowEducationWork::setAsRow(int number)
{
    ui->frame->setMaximumHeight(ROW_HEIGHT);
    ui->frame->setMinimumHeight(ROW_HEIGHT);

    WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});

    m_firstPlan = ui->lbl_I_plan;
    m_secondPlan = ui->lbl_II_plan;
    m_firstFact = ui->lbl_I_fact;
    m_secondFact = ui->lbl_II_fact;
    m_totalPlan = ui->lbl_yearPlan;
    m_totalFact = ui->lbl_yearFact;

    connect(ui->btn_delete, &QPushButton::clicked, this, &RowEducationWork::deleteWork);
    setRow(number);
    setModels();
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

    m_firstPlan = ui->lbl_I_totalPlan;
    m_secondPlan = ui->lbl_II_totalPlan;
    m_firstFact = ui->lbl_I_totalFact;
    m_secondFact = ui->lbl_II_totalFact;
    m_totalPlan = ui->lbl_yearTotalPlan;
    m_totalFact = ui->lbl_yearTotalFact;

    auto weekRow = new WeekEducationWork(true, true, this);
    addWeeks(weekRow);
    setTotal();
}

void RowEducationWork::setTotal()
{
    m_firstPlan->setNum(m_totalHours.firstPlane());
    m_secondPlan->setNum(m_totalHours.secondPlane());
    m_firstFact->setNum(m_totalHours.firstFact());
    m_secondFact->setNum(m_totalHours.secondFact());
    m_totalPlan->setNum(m_totalHours.firstPlane() + m_totalHours.secondPlane());
    m_totalFact->setNum(m_totalHours.firstFact() + m_totalHours.secondFact());

    emit totalChanged(m_workType, &m_totalHours);
}

void RowEducationWork::saveWorkData()
{
    emit saveWork(m_work);
    setSaved(m_work->id());
}

void RowEducationWork::makeConnects()
{
    connect(ui->cb_discipline, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setDiscipline);
    connect(ui->cb_course, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setCourse);
    connect(ui->cb_workForm, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setWorkForm);
    connect(ui->sb_groupCount, QOverload<int>::of(&QSpinBox::valueChanged), this, &RowEducationWork::setGroupCount);
}

void RowEducationWork::makeDisconnects()
{
    disconnect(ui->cb_discipline, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setDiscipline);
    disconnect(ui->cb_course, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setCourse);
    disconnect(ui->cb_workForm, QOverload<int>::of(&ComboBox::currentIndexChanged), this, &RowEducationWork::setWorkForm);
    disconnect(ui->sb_groupCount, QOverload<int>::of(&QSpinBox::valueChanged), this, &RowEducationWork::setGroupCount);
}

void RowEducationWork::setAsHeader()
{
    ui->frame->setMaximumHeight(HEADER_HEIGHT);
    ui->frame->setMinimumHeight(HEADER_HEIGHT);
    addWeeks(new MonthHeader(this));
}

void RowEducationWork::setDiscipline(int index)
{
    int id = m_disciplines.data(m_disciplines.index(index, 0), DictionaryModel::Id).toInt();
    if(id)
        m_work->setDisciplineId(id);
    saveWorkData();
}

void RowEducationWork::setCourse(int index)
{
    int id = m_courses.data(m_courses.index(index, 0), DictionaryModel::Id).toInt();
    if(id)
        m_work->setCourseId(id);
    saveWorkData();
}

void RowEducationWork::setWorkForm(int index)
{
    int id = m_workForm.data(m_workForm.index(index, 0), DictionaryModel::Id).toInt();
    if(id)
        m_work->setWorkFormId(id);
    saveWorkData();
}

void RowEducationWork::setGroupCount(int val)
{
    m_work->setGroupCount(val);
    saveWorkData();
}

