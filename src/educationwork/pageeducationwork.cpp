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

void PageEducationWork::swapItems(bool down)
{
    QModelIndex index =  ui->lv_educationWorks->currentIndex();
    int currentRow = index.row();
    int needRow = currentRow + (down ? 1 : -1);             //Если down добавляем еденицу к номеру строки
    m_model.swapItems(currentRow, needRow);
    QModelIndex indx = m_model.index(needRow, index.column());
    // ui->lv_educationWorks->setCurrentIndex(m_model.index(needRow, index.column()));
    ui->lv_educationWorks->edit(indx);
}

void PageEducationWork::on_btn_add_clicked()
{

}

void PageEducationWork::deleteRow()
{

}

void PageEducationWork::on_btn_up_clicked()
{
    if(ui->lv_educationWorks->currentIndex().row() <= 0)
        return;

    swapItems(false);
}

void PageEducationWork::on_btn_down_clicked()
{
    if(ui->lv_educationWorks->currentIndex().row() >= m_model.rowCount() - 1)
        return;

    swapItems(true);
}
