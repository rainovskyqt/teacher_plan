#include "genericfooter.h"
#include "ui_genericfooter.h"

#include <QScrollBar>

GenericFooter::GenericFooter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenericFooter)
{
    ui->setupUi(this);
}

GenericFooter::~GenericFooter()
{
    delete ui;
}

int GenericFooter::totalPlane() const
{
    return ui->lbl_plan->text().toInt();
}

int GenericFooter::totalFact() const
{
    return ui->lbl_fact->text().toInt();
}

void GenericFooter::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void GenericFooter::setValues(int plan, int fact)
{
    ui->lbl_plan->setText(QString::number(plan));
    ui->lbl_fact->setText(QString::number(fact));
}
