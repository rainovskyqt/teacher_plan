#include "formtotaltime.h"
#include "status.h"
#include "ui_formtotaltime.h"

#include "database/database.h"

#define MAX_FULL_RATE_HOURS 1512
#define MAX_FULL_RATE_EDUCATIONAL_HOURS 900

FormTotalTime::FormTotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTotalTime)
{
    ui->setupUi(this);
    createConnections();
    makeTimeConnections();
}

FormTotalTime::~FormTotalTime()
{
    delete ui;
}

void FormTotalTime::setPlanData(TeacherPlan *plan)
{
    setRate(plan->rate());
}

void FormTotalTime::clearHours()
{
    auto hours = this->findChildren<QSpinBox*>();
    for(auto h: hours)
        h->setValue(0);
}

void FormTotalTime::setPlanTime(WorkType type, PlanTime::Semester semester, int val)
{
    QString name = QString();

    switch (type) {
    case WorkType::Educational:
        name = "sb_edu";
        break;
    case WorkType::MethodicWork:
        name = "sb_metod";
        break;
    case WorkType::ResearchingWork:
        name = "sb_reseach";
        break;
    case WorkType::SportWork:
        name = "sb_sport";
        break;
    case WorkType::OtherWork:
        name = "sb_other";
        break;
    }

    switch (semester) {
    case PlanTime::FirstSemester:
        name += "FirstSemester";
        break;
    case PlanTime::SecondSemestr:
        name += "SecondSemester";
        break;
    }

    auto time = this->findChild<QSpinBox*>(name);;
    if(time)
        time->setValue(val);
}

void FormTotalTime::setRate(double rate)
{
    foreach (auto btn, m_rateGroup->buttons()) {
        if(btn->property("rate").toDouble() == rate){
            btn->setChecked(true);

            int edHours = MAX_FULL_RATE_EDUCATIONAL_HOURS * rate;
            ui->lbl_eduMaxHours->setProperty("hours", edHours);
            ui->lbl_eduMaxHours->setProperty("exactly", false);
            ui->lbl_eduMaxHours->setText(QString("<= %1 часов").arg(edHours));

            int total = MAX_FULL_RATE_HOURS * rate;
            ui->lbl_totalMaxHours->setProperty("hours", total);
            ui->lbl_totalMaxHours->setProperty("exactly", true);
            ui->lbl_totalMaxHours->setText(QString("= %1 часов").arg(total));
            break;
        }
    }
    colorHours(ui->lbl_eduMaxHours, ui->sb_eduYear);
    colorHours(ui->lbl_totalMaxHours, ui->sb_totalYear);
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
                    setRate(rate);
                    emit rateChanged(rate);
                }
            });
}

void FormTotalTime::colorHours(QLabel *lbl, QSpinBox *sBox)
{
    int max = lbl->property("hours").toInt();
    int value = sBox->value();
    bool exactly =  lbl->property("exactly").toBool();


    if(value > max){
        sBox->setStyleSheet(Status::more());
    } else if (sBox->value() < max) {
        if(exactly || (value < max * 0.85))
            sBox->setStyleSheet(Status::less());
        else {
            sBox->setStyleSheet(Status::equal());
        }
    } else {
        sBox->setStyleSheet(Status::equal());
    }

    if(sBox->value() < max){
    }
    else if(sBox->value() > max)
        sBox->setStyleSheet(Status::more());
    else
        sBox->setStyleSheet(Status::equal());
}

void FormTotalTime::makeTimeConnections()
{
    connect(ui->sb_eduFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_eduSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_metodFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_metodSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_otherFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_otherSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_reseachFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_reseachSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_sportFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_sportSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_totalFirstSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
    connect(ui->sb_totalSecondSemester, qOverload<int>(&QSpinBox::valueChanged), this, &FormTotalTime::countYearTime);
}

void FormTotalTime::countFirstSemester()
{
    ui->sb_totalFirstSemester->setValue(
        ui->sb_eduFirstSemester->value() +
        ui->sb_metodFirstSemester->value() +
        ui->sb_otherFirstSemester->value() +
        ui->sb_reseachFirstSemester->value() +
        ui->sb_sportFirstSemester->value()
        );
}

void FormTotalTime::countSecondSemester()
{
    ui->sb_totalSecondSemester->setValue(
        ui->sb_eduSecondSemester->value() +
        ui->sb_metodSecondSemester->value() +
        ui->sb_otherSecondSemester->value() +
        ui->sb_reseachSecondSemester->value() +
        ui->sb_sportSecondSemester->value()
        );
}

void FormTotalTime::on_sb_eduYear_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
    colorHours(ui->lbl_eduMaxHours, ui->sb_eduYear);
    emit educationYearHours(arg1);
}


void FormTotalTime::on_sb_totalYear_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
    colorHours(ui->lbl_totalMaxHours, ui->sb_totalYear);
}

void FormTotalTime::countYearTime()
{
    auto name = sender()->objectName();
    if(name.contains("sb_edu")){
        ui->sb_eduYear->setValue(ui->sb_eduFirstSemester->value() + ui->sb_eduSecondSemester->value());
        countFirstSemester();
        countSecondSemester();
    } else if(name.contains("sb_metod")){
        ui->sb_metodYear->setValue(ui->sb_metodFirstSemester->value() + ui->sb_metodSecondSemester->value());
        countFirstSemester();
        countSecondSemester();
    }else if(name.contains("sb_other")){
        ui->sb_otherYear->setValue(ui->sb_otherFirstSemester->value() + ui->sb_otherSecondSemester->value());
        countFirstSemester();
        countSecondSemester();
    }else if(name.contains("sb_reseach")){
        ui->sb_reseachYear->setValue(ui->sb_reseachFirstSemester->value() + ui->sb_reseachSecondSemester->value());
        countFirstSemester();
        countSecondSemester();
    }else if(name.contains("sb_sport")){
        ui->sb_sportYear->setValue(ui->sb_sportFirstSemester->value() + ui->sb_sportSecondSemester->value());
        countFirstSemester();
        countSecondSemester();
    }else if(name.contains("sb_total")){
        ui->sb_totalYear->setValue(ui->sb_totalFirstSemester->value() + ui->sb_totalSecondSemester->value());
    }
}

