#include "pageeducationwork.h"
#include "ui_pageeducationwork.h"

#include "delegateeducationwork.h"
#include "roweducationwork.h"

#include <QMessageBox>


PageEducationWork::PageEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageEducationWork)
{
    ui->setupUi(this);

    DelegateEducationWork *delegate = new DelegateEducationWork(ui->lv_educationWorks);
    ui->lv_educationWorks->setModel(&m_model);
    ui->lv_educationWorks->setItemDelegate(delegate);
}

PageEducationWork::~PageEducationWork()
{
    delete ui;
}

void PageEducationWork::setPlan(int planId)
{
    m_model.loadData(planId);
    qApp->setOverrideCursor(Qt::ArrowCursor);
}

// void PageEducationWork::setStaff(int staffId)
// {
//     m_model.loadData(staffId);


//     qApp->setOverrideCursor(Qt::ArrowCursor);
// }

void PageEducationWork::fillTable()
{
    clearData();

    // auto works = m_model.works();
    // for(const auto &work: qAsConst(works)){
    //     addRow(ui->lw_educationWork->count(), work);
    // }
}

// void PageEducationWork::addRow(int row, const ModelEducationWork::EducationWork &work)
// {
    // auto item = new QListWidgetItem();
    // auto rowWidget = new RowEducationWork(row + 1, work, item);
    // item->setSizeHint(rowWidget->sizeHint());
    // ui->lw_educationWork->insertItem(row, item);
    // ui->lw_educationWork->setItemWidget(item, rowWidget);

    // connect(rowWidget, &RowEducationWork::deleteWork, this, &PageEducationWork::deleteRow);

        //     connect(row, &EducationRow::valueChanged, this, [this](EducationalHour *hour){
        //         auto h = new EducationalHour(-1, -1, hour->week(), countHours(hour->type(), hour->week()),
        //                                      hour->type(), ui->w_footer);
        //         ui->w_footer->setValue(h);
        //     });

    //     connect(row, &EducationRow::factValueChanged, this, &FormEducationWork::factValueChanged);
    //     connect(ui->scrolbar, &QScrollBar::valueChanged, row, &EducationRow::setScrolBarValue);

    //     row->loadHours();           //Часы устанасливаются после подключения сигнала к футеру, что бы сработал посчет часов
// }

void PageEducationWork::clearData()
{
    // ui->lw_educationWork->clear();
    // ui->w_footer->clear();
    // auto rows = this->findChildren<EducationRow*>();
    // qDeleteAll(rows.begin(), rows.end());
    // emit clear();
}

void PageEducationWork::updateRowNumber(int start)
{
    // for(int i = start; i < ui->lw_educationWork->count(); ++i){
    //     auto row = dynamic_cast<RowEducationWork*>(ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(i)));
    //     row->setRow(i + 1);
    // }
}

void PageEducationWork::swapItems(int fromRow, int toRow)
{
    // auto rowWidget = ui->lw_educationWork->itemWidget(ui->lw_educationWork->item(fromRow));
    // auto row = static_cast<RowEducationWork*>(rowWidget);

    // if(!row)
    //     return;

    // auto work = row->work();
    // delete ui->lw_educationWork->takeItem(fromRow);

    // addRow(toRow, work);
    // ui->lw_educationWork->setCurrentRow(toRow);
    // updateRowNumber(fromRow > toRow ? toRow : fromRow);
}

void PageEducationWork::on_btn_add_clicked()
{
    // addRow(ui->lw_educationWork->count(), {});
}

void PageEducationWork::deleteRow()
{
    // auto workRow = dynamic_cast<RowEducationWork*>(sender());
    // if(QMessageBox::question(this,
    //                           "Удаление",
    //                           QString("Удалить %1 из списка?").arg(workRow->toString()))
    //     == QMessageBox::No)
    //     return;

    // m_model.deleteWork(workRow->id());

    // int row = workRow->row() - 1;

    // delete ui->lw_educationWork->item(row);
    // updateRowNumber(row);
}

void PageEducationWork::on_btn_up_clicked()
{
    // auto list = ui->lw_educationWork;
    // int cRow = list->currentRow();
    // if(!cRow)
    //     return;
    // swapItems(cRow, cRow - 1);
}

void PageEducationWork::on_btn_down_clicked()
{
    // auto list = ui->lw_educationWork;
    // int cRow = list->currentRow();
    // if(cRow >= list->count() - 1)
    //     return;
    // swapItems(cRow, cRow + 1);
}
