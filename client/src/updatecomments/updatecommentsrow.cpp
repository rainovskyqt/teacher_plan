#include "updatecommentsrow.h"
#include "ui_updatecommentsrow.h"

#include <QDate>

UpdateCommentsRow::UpdateCommentsRow(int id, QString date, QString version, QString text, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UpdateCommentsRow)
{
    ui->setupUi(this);
    m_baseId = id;
    ui->lbl_date->setText(date);
    ui->lbl_version->setText(version);
    ui->lbl_text->setText(text);
}

UpdateCommentsRow::~UpdateCommentsRow()
{
    delete ui;
}

int UpdateCommentsRow::baseId() const
{
    return m_baseId;
}
