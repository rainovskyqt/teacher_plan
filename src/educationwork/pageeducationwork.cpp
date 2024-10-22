#include "pageeducationwork.h"
#include "ui_pageeducationwork.h"

#include "roweducationwork.h"

#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

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

void PageEducationWork::setPlan(int staffId)
{
    m_readySave = false;

    m_model.loadData(staffId);
    addHeader();
    addFooter();
    fillTable();

    m_readySave = true;

}

void PageEducationWork::fillTable()
{
    clearData();
    using F = ModelEducationWork::Fields;
    for(int row = 0; row < m_model.rowCount(); ++row){
        const ModelEducationWork::EducationWork work(
            m_model.data(m_model.index(row, (int)F::WorkId)).toInt(),
            m_model.data(m_model.index(row, (int)F::DisciplineId)).toInt(),
            m_model.data(m_model.index(row, (int)F::CourseId)).toInt(),
            m_model.data(m_model.index(row, (int)F::WorkFormId)).toInt(),
            m_model.data(m_model.index(row, (int)F::GroupCount)).toInt(),
            m_model.data(m_model.index(row, (int)F::Comments)).toString(),
            m_model.data(m_model.index(row, (int)F::OrderPalce)).toInt(),
            m_model.hours(row)
            );
        addRow(row, work);
    }
}

void PageEducationWork::addRow(int row, const ModelEducationWork::EducationWork &work)
{
    auto item = new QListWidgetItem();
    auto rowWidget = new RowEducationWork(row, work, RowEducationWork::Position::Row, true, ui->lw_educationWork);
    item->setSizeHint(QSize(ui->lw_educationWork->width() - SCROLLBAR_WIGHT, rowWidget->sizeHint().height()));
    ui->lw_educationWork->insertItem(row, item);
    ui->lw_educationWork->setItemWidget(item, rowWidget);

    connect(ui->hsb_scroller, &QScrollBar::valueChanged, rowWidget, &RowEducationWork::setSliderPosition);
    connect(rowWidget, &RowEducationWork::deleteWork, this, &PageEducationWork::deleteRow);
    // connect(rowWidget, &RowEducationWork::updateValues, this, &ModelEducationWork::updateValues);


    //     connect(row, &EducationRow::valueChanged, this, [this](EducationalHour *hour){
    //         auto h = new EducationalHour(-1, -1, hour->week(), countHours(hour->type(), hour->week()),
    //                                      hour->type(), ui->w_footer);
    //         ui->w_footer->setValue(h);
    //     });

    //     connect(row, &EducationRow::factValueChanged, this, &FormEducationWork::factValueChanged);
    //     connect(ui->scrolbar, &QScrollBar::valueChanged, row, &EducationRow::setScrolBarValue);

    //     row->loadHours();           //Часы устанасливаются после подключения сигнала к футеру, что бы сработал посчет часов
}

void PageEducationWork::clearData()
{
    ui->lw_educationWork->clear();
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

void PageEducationWork::addNewRow()
{
    addRow(ui->lw_educationWork->count(), {});
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
    m_header = new RowEducationWork(0, {}, RowEducationWork::Position::Header, true, this);
    ui->vl_header->addWidget(m_header);
    connect(ui->hsb_scroller, &QScrollBar::valueChanged, m_header, &RowEducationWork::setSliderPosition);
}

void PageEducationWork::addFooter()
{
    clearLayout(ui->vl_footer);
    m_footer = new RowEducationWork(0, {}, RowEducationWork::Position::Footer, true, this);
    ui->vl_footer->addWidget(m_footer);
    connect(ui->hsb_scroller, &QScrollBar::valueChanged, m_footer, &RowEducationWork::setSliderPosition);
    connect(m_footer, &RowEducationWork::addNewRow, this, &PageEducationWork::addNewRow);
    connect(m_footer, &RowEducationWork::rowUpClicked, this, &PageEducationWork::rowUp);
    connect(m_footer, &RowEducationWork::rowDownClicked, this, &PageEducationWork::rowDown);
}
