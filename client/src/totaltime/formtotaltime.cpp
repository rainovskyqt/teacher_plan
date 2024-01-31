#include "formtotaltime.h"
#include "ui_formtotaltime.h"

#include "database/database.h"
#include <QButtonGroup>
#include <QHeaderView>

FormTotalTime::FormTotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTotalTime)
{
    ui->setupUi(this);

    createConnections();

    loadHours();
}

FormTotalTime::~FormTotalTime()
{
    delete ui;
}

void FormTotalTime::on_btn_save_clicked()
{
}

void FormTotalTime::createConnections()
{
    createRateConnections();

    connect(ui->sb_totalFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_totalYear->setValue(ui->sb_totalSecond->value() + value);
    });

    connect(ui->sb_totalSecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_totalYear->setValue(ui->sb_totalFirst->value() + value);
    });

    connect(ui->sb_studyFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_studyYear->setValue(ui->sb_studySecond->value() + value);
        ui->sb_totalFirst->setValue(value + ui->sb_methodicFirst->value() + ui->sb_searchingFirst->value() + ui->sb_sportFirst->value() + ui->sb_otherFirst->value());
    });

    connect(ui->sb_studySecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_studyYear->setValue(ui->sb_studyFirst->value() + value);
        ui->sb_totalSecond->setValue(value + ui->sb_methodicSecond->value() + ui->sb_searchingSecond->value() +ui->sb_sportSecond->value() + ui->sb_otherSecond->value());
    });

    connect(ui->sb_methodicFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_methodicYear->setValue(ui->sb_methodicSecond->value() + value);
        ui->sb_totalFirst->setValue(value + ui->sb_studyFirst->value() + ui->sb_searchingFirst->value() + ui->sb_sportFirst->value() + ui->sb_otherFirst->value());
    });

    connect(ui->sb_methodicSecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_methodicYear->setValue(ui->sb_studyFirst->value() + value);
        ui->sb_totalSecond->setValue(value + ui->sb_studySecond->value() + ui->sb_searchingSecond->value() + ui->sb_sportSecond->value() + ui->sb_otherSecond->value());
    });

    connect(ui->sb_searchingFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_searchingYear->setValue(ui->sb_searchingSecond->value() + value);
        ui->sb_totalFirst->setValue(value + ui->sb_studyFirst->value() + ui->sb_methodicFirst->value() + ui->sb_sportFirst->value() + ui->sb_otherFirst->value());
    });

    connect(ui->sb_searchingSecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_searchingYear->setValue(ui->sb_searchingFirst->value() + value);
        ui->sb_totalSecond->setValue(value + ui->sb_studySecond->value() + ui->sb_methodicSecond->value() + ui->sb_sportSecond->value() + ui->sb_otherSecond->value());
    });

    connect(ui->sb_sportFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_sportYear->setValue(ui->sb_sportSecond->value() + value);
        ui->sb_totalFirst->setValue(value + ui->sb_studyFirst->value() + ui->sb_methodicFirst->value() + ui->sb_searchingFirst->value() + ui->sb_otherFirst->value());
    });

    connect(ui->sb_sportSecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_sportYear->setValue(ui->sb_sportFirst->value() + value);
        ui->sb_totalSecond->setValue(value + ui->sb_studySecond->value() + ui->sb_methodicSecond->value() + ui->sb_searchingFirst->value() + ui->sb_otherSecond->value());
    });

    connect(ui->sb_otherFirst, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_otherYear->setValue(ui->sb_otherSecond->value() + value);
        ui->sb_totalFirst->setValue(value + ui->sb_studyFirst->value() + ui->sb_methodicFirst->value() + ui->sb_searchingFirst->value() + ui->sb_sportFirst->value());
    });

    connect(ui->sb_otherSecond, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        ui->sb_otherYear->setValue(ui->sb_otherFirst->value() + value);
        ui->sb_totalSecond->setValue(value + ui->sb_studySecond->value() + ui->sb_methodicSecond->value() + ui->sb_searchingFirst->value() + ui->sb_sportSecond->value());
    });

    connect(ui->sb_totalYear, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int value){
        if(value > m_totalTimeList->maxHoursCount(m_rate)){
            ui->sb_totalYear->setStyleSheet("background-color: rgb(255, 0, 0);");
            ui->w_totalInput->setVisible(true);
        }else if(value == m_totalTimeList->maxHoursCount(m_rate)){
            ui->sb_totalYear->setStyleSheet("background-color: rgb(0, 255, 0);");
            ui->w_totalInput->setVisible(false);
        } else {
            ui->sb_totalYear->setStyleSheet("background-color: rgb(255, 255, 0);");
            ui->w_totalInput->setVisible(true);
        }
    });

}

void FormTotalTime::createRateConnections()
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
            m_rate = btn->property("rate").toDouble();
            qDebug() << m_rate;
        }
        ui->lbl_maxHoursMessage->setText(QString("Должно быть ровно\n%1 часов").arg(m_totalTimeList->maxHoursCount(m_rate)));
    });
}

void FormTotalTime::setHoursInForm(TotalTimeList *totalTime)
{
    ui->rb_quaterTime->setChecked(true);
}

void FormTotalTime::loadHours()
{
    m_totalTimeList = Database::instance().getTotaTimeList();

    setHoursInForm(m_totalTimeList);
}

