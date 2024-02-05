#include "formtotaltime.h"
#include "ui_formtotaltime.h"

#include "database/database.h"
#include <QButtonGroup>


FormTotalTime::FormTotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTotalTime)
{
    ui->setupUi(this);

    setTable();
    createConnections();
    ui->tv_totalHours->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

FormTotalTime::~FormTotalTime()
{
    delete ui;
}

void FormTotalTime::setTable()
{
    ui->tv_totalHours->setHorizontalHeader(new HierarchicalHeaderView(Qt::Horizontal, ui->tv_totalHours));
    ui->tv_totalHours->setModel(&m_model);
    ui->tv_totalHours->resizeColumnsToContents();
}

void FormTotalTime::createConnections()
{
    QButtonGroup *group = new QButtonGroup(this);
    ui->rb_fullTime->setProperty("rate", 1);
    group->addButton(ui->rb_fullTime);

    ui->rb_threeQuaters->setProperty("rate", 0.75);
    group->addButton(ui->rb_threeQuaters);

    ui->rb_halfTime->setProperty("rate", 0.5);
    group->addButton(ui->rb_halfTime);

    ui->rb_quaterTime->setProperty("rate", 0.25);
    group->addButton(ui->rb_quaterTime);

    connect(group, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled), this, [&](QAbstractButton *btn, bool checked){
        if(checked){
            m_model.setRate(btn->property("rate").toDouble());
        }
    });
}

