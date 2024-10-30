#include "pageeducationwork.h"
#include "ui_pageeducationwork.h"

#include "roweducationwork.h"

#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

#include <user/usermanager.h>

#include <teacherplan/planemanager.h>

#define SCROLLBAR_WIGHT 15

PageEducationWork::PageEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageEducationWork)
{
    ui->setupUi(this);
}

PageEducationWork::~PageEducationWork()
{
    delete ui;
}

void PageEducationWork::resizeEvent(QResizeEvent *e)
{
    ui->hsb_scroller->setMaximum(m_header->sliderWight());
    updateRowsSizeHint();
    QWidget::resizeEvent(e);
}

void PageEducationWork::setPlan(int planId)
{
    m_readySave = false;

    addHeader();
    addFooter();
    fillTable(planId);
    resetScrollbar();
    updateTotal();

    m_planId = planId;

    m_readySave = true;
}

void PageEducationWork::setOwnPlan(int staff)
{
    bool own = UserManager::get()->userStaff(staff);
    if(m_ownPlan == own)
        return;

    m_ownPlan = own;
    updateOwn(m_ownPlan);
}

void PageEducationWork::fillTable(int staffId)
{
    clearData();
    m_edWorks = m_model.loadData(staffId);

    for(int row = 0; row < m_edWorks.count(); ++row){
        addRow(row, m_edWorks.at(row));
    }
}

void PageEducationWork::addRow(int row, EducationWork *work)
{
    auto item = new QListWidgetItem();
    auto rowWidget = new RowEducationWork(row, RowEducationWork::Position::Row, !m_ownPlan, ui->lw_educationWork);
    item->setSizeHint(QSize(ui->lw_educationWork->width() - SCROLLBAR_WIGHT, rowWidget->sizeHint().height()));
    ui->lw_educationWork->insertItem(row, item);
    ui->lw_educationWork->setItemWidget(item, rowWidget);

    connect(ui->hsb_scroller, &QScrollBar::valueChanged, rowWidget, &RowEducationWork::setSliderPosition);
    connect(rowWidget, &RowEducationWork::deleteWork, this, &PageEducationWork::deleteRow);
    connect(rowWidget, &RowEducationWork::valueChanged, this, &PageEducationWork::updateValues);
    connect(rowWidget, &RowEducationWork::saveWork, this, &PageEducationWork::saveWork);

    rowWidget->setWorkData(work);
}

void PageEducationWork::clearData()
{
    ui->lw_educationWork->clear();
    qDeleteAll(m_edWorks.begin(), m_edWorks.end());
    m_edWorks.clear();
    emit clear();
}

void PageEducationWork::updateRowNumber(int start)
{
    for(int i = start; i < ui->lw_educationWork->count(); ++i){
        auto row = dynamic_cast<RowEducationWork*>(ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(i)));
        row->setRow(i);
    }
}

void PageEducationWork::swapItems(int fromRow, int toRow)
{
    auto rowWidget = ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(fromRow));
    auto row = static_cast<RowEducationWork*>(rowWidget);

    if(!row)
        return;

    auto work = row->work();
    delete ui->lw_educationWork->takeItem(fromRow);

    addRow(toRow, work);
    ui->lw_educationWork->setCurrentRow(toRow);
    updateRowNumber(fromRow > toRow ? toRow : fromRow);
}

void PageEducationWork::updateRowsSizeHint()
{
    for(int i = 0; i < ui->lw_educationWork->count(); ++i){
        auto row = ui->lw_educationWork->item(i);
        row->setSizeHint(QSize(ui->lw_educationWork->width() - 15, row->sizeHint().height()));
    }
}

void PageEducationWork::clearLayout(QLayout *la)
{
    while (QLayoutItem* item = la->takeAt(0)) {
        delete item->widget();
        delete item;
    }
}

void PageEducationWork::resetScrollbar()
{
    ui->hsb_scroller->setValue(0);
}

void PageEducationWork::updateTotal()
{
    qDeleteAll(m_totalHours.begin(), m_totalHours.end());
    m_totalHours.clear();

    for(EducationWork *w : qAsConst(m_edWorks)){
        auto workHours = w->hours();
        for(auto it = workHours.begin(); it != workHours.end(); ++it){
            int week = it.key();
            Hour *h = m_totalHours[week];
            if(!h)
                h = new Hour(this);
            h->setPlan(it.value()->plan() + h->plan());
            h->setFact(it.value()->fact() + h->fact());
            m_totalHours.insert(week, h);
        }
    }

    m_footer->setHours(m_totalHours);
}

void PageEducationWork::saveNewValue(EducationWork *w, int week)
{
    if(m_readySave)
        m_model.saveHours(w, week);
}

void PageEducationWork::updateOwn(bool own)
{

}

void PageEducationWork::addNewRow()
{
    EducationWork *work = new EducationWork(&m_model);
    work->setTeacherPlanId(m_planId);
    work->setOrderPlace(ui->lw_educationWork->count() + 1);
    m_edWorks.append(work);
    addRow(ui->lw_educationWork->count(), work);
}

void PageEducationWork::updateValues(EducationWork *w, int week)
{
    updateTotal();
    saveNewValue(w, week);
}

void PageEducationWork::setSliderMaximum(int max)
{
    ui->hsb_scroller->setMaximum(max);
}

void PageEducationWork::saveWork(EducationWork *w)
{
    m_model.saveWork(w);
}

void PageEducationWork::deleteRow()
{
    auto workRow = dynamic_cast<RowEducationWork*>(sender());
    if(QMessageBox::question(this,
                              "Удаление",
                              QString("Удалить %1 из списка?").arg(workRow->toString()))
        == QMessageBox::No)
        return;

    m_model.deleteWork(workRow->id());

    int row = workRow->row();

    delete ui->lw_educationWork->item(row);
    updateRowNumber(row);
}

void PageEducationWork::rowUp()
{
    auto list = ui->lw_educationWork;
    int cRow = list->currentRow();
    if(!cRow)
        return;
    swapItems(cRow, cRow - 1);
}

void PageEducationWork::rowDown()
{
    auto list = ui->lw_educationWork;
    int cRow = list->currentRow();
    if(cRow >= list->count() - 1)
        return;
    swapItems(cRow, cRow + 1);
}

void PageEducationWork::addHeader()
{
    clearLayout(ui->vl_header);
    m_header = new RowEducationWork(0, RowEducationWork::Position::Header, true, this);
    ui->vl_header->addWidget(m_header);
    connect(ui->hsb_scroller, &QScrollBar::valueChanged, m_header, &RowEducationWork::setSliderPosition);
}

void PageEducationWork::addFooter()
{
    clearLayout(ui->vl_footer);
    m_footer = new RowEducationWork(0, RowEducationWork::Position::Footer, !m_ownPlan, this);
    ui->vl_footer->addWidget(m_footer);
    connect(ui->hsb_scroller, &QScrollBar::valueChanged, m_footer, &RowEducationWork::setSliderPosition);
    connect(m_footer, &RowEducationWork::addNewRow, this, &PageEducationWork::addNewRow);
    connect(m_footer, &RowEducationWork::rowUpClicked, this, &PageEducationWork::rowUp);
    connect(m_footer, &RowEducationWork::rowDownClicked, this, &PageEducationWork::rowDown);
    connect(m_footer, &RowEducationWork::totalChanged, this, &PageEducationWork::totalChanged);
}
