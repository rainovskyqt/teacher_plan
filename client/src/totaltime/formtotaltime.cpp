#include "formtotaltime.h"
#include "ui_formtotaltime.h"

#include "database/database.h"

FormTotalTime::FormTotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTotalTime)
{
    ui->setupUi(this);

    ui->btn_reset->setVisible(false);

    setTable();
    createConnections();
    ui->tv_totalHours->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->btn_save->setEnabled(false);

    connect(ui->btn_reset, &QPushButton::clicked, &m_model, &ModelTotalTime::reset);
    connect(&m_model, &ModelTotalTime::dataChanged, this, [this]{
        emit modelDataChanged();
        ui->btn_save->setEnabled(true);
    });

    connect(ui->btn_save, &QPushButton::clicked, this, &FormTotalTime::savePlan);
}

FormTotalTime::~FormTotalTime()
{
    delete ui;
}

void FormTotalTime::setPlaneData(TeacherPlan *plan)
{
    setRate(plan->rate());
    m_model.setHours(plan);
    plan->setChanged(false);
}

void FormTotalTime::setRate(double rate)
{
    foreach (auto btn, m_rateGroup->buttons()) {
        if(btn->property("rate").toDouble() == rate){
            btn->setChecked(true);
            return;
        }
    }
}

void FormTotalTime::setTable()
{
    ui->tv_totalHours->setHorizontalHeader(new HierarchicalHeaderView(Qt::Horizontal, ui->tv_totalHours));
    ui->tv_totalHours->setModel(&m_model);
    ui->tv_totalHours->resizeColumnsToContents();
}

void FormTotalTime::createConnections()
{
    m_rateGroup = new QButtonGroup(this);
    ui->rb_fullTime->setProperty("rate", 1);
    m_rateGroup->addButton(ui->rb_fullTime);

    ui->rb_threeQuaters->setProperty("rate", 0.75);
    m_rateGroup->addButton(ui->rb_threeQuaters);

    ui->rb_halfTime->setProperty("rate", 0.5);
    m_rateGroup->addButton(ui->rb_halfTime);

    ui->rb_quaterTime->setProperty("rate", 0.25);
    m_rateGroup->addButton(ui->rb_quaterTime);

    connect(m_rateGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
            this, [&](QAbstractButton *btn, bool checked){
                if(checked){
                    auto rate = btn->property("rate").toDouble();
                    m_model.setRate(rate);
                    emit rateChanged(rate);
                }
            });
}
