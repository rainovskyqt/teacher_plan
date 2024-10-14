#include "weekeducationwork.h"
#include "ui_weekeducationwork.h"

#include <QIntValidator>

WeekEducationWork::WeekEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekEducationWork)
{
    ui->setupUi(this);
    ui->line_plane->setValidator(new QIntValidator(0, 1000, this));
    ui->line_fact->setValidator(new QIntValidator(0, 1000, this));
}

WeekEducationWork::~WeekEducationWork()
{
    delete ui;
}
