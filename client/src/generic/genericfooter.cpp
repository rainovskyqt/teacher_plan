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

void GenericFooter::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}
