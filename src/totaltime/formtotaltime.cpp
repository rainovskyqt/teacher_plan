#include "formtotaltime.h"
#include "status.h"

#include "ui_formtotaltime.h"
#include <QList>
#include <QMap>
#include "database/database.h"

#define MAX_FULL_RATE_HOURS 1512
#define MAX_FULL_RATE_EDUCATIONAL_HOURS 900

FormTotalTime::FormTotalTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormTotalTime)
{
    ui->setupUi(this);
    createConnections();
}

FormTotalTime::~FormTotalTime()
{
    delete ui;
}

void FormTotalTime::updateValues(WorkType type, const TotalHour *vals)
{
    m_totalHours.setHours(type, vals);
    setValues();
}

void FormTotalTime::changeRate(bool toggled)
{
    if(!toggled)
        return;

    QRadioButton *btn = static_cast<QRadioButton*>(sender());
    auto rate = btn->property("rate").toDouble();
    emit rateChanged(rate);
}

void FormTotalTime::setRate(double rate)
{
    int edHours = MAX_FULL_RATE_EDUCATIONAL_HOURS * rate;
    ui->lbl_eduMaxHours->setProperty("hours", edHours);
    ui->lbl_eduMaxHours->setProperty("exactly", false);
    ui->lbl_eduMaxHours->setText(QString("<= %1 часов").arg(edHours));

    int total = MAX_FULL_RATE_HOURS * rate;
    ui->lbl_totalMaxHours->setProperty("hours", total);
    ui->lbl_totalMaxHours->setProperty("exactly", true);
    ui->lbl_totalMaxHours->setText(QString("= %1 часов").arg(total));

    colorHours();
    setRateBtn(rate);
}

void FormTotalTime::colorHours()
{
    colorHour(ui->lbl_eduMaxHours, ui->sb_eduYear);
    colorHour(ui->lbl_totalMaxHours, ui->sb_totalYear);
}

void FormTotalTime::colorHour(QLabel *lbl, QSpinBox *sBox)
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

void FormTotalTime::createConnections()
{
    auto btns = this->findChildren<QRadioButton*>();
    for(auto b : btns)
        connect(b, &QRadioButton::toggled, this, &FormTotalTime::changeRate);
}

void FormTotalTime::setValues()
{
    setValue(ui->sb_eduFirstSemester, ui->sb_eduSecondSemester, ui->sb_eduYear, m_totalHours.getHours(WorkType::Educational));
    setValue(ui->sb_metodFirstSemester, ui->sb_metodSecondSemester, ui->sb_metodYear, m_totalHours.getHours(WorkType::MethodicWork));
    setValue(ui->sb_reseachFirstSemester, ui->sb_reseachSecondSemester, ui->sb_reseachYear, m_totalHours.getHours(WorkType::ResearchingWork));
    setValue(ui->sb_sportFirstSemester, ui->sb_sportSecondSemester, ui->sb_sportYear, m_totalHours.getHours(WorkType::SportWork));
    setValue(ui->sb_otherFirstSemester, ui->sb_otherSecondSemester, ui->sb_otherYear, m_totalHours.getHours(WorkType::OtherWork));

    setTotal();

    colorHours();
}

void FormTotalTime::setValue(QSpinBox *first, QSpinBox *second, QSpinBox *total, const TotalHour *vals)
{
    if(!vals)
        return;

    int fVal = vals->firstPlane();
    int sVal = vals->secondPlane();
    first->setValue(fVal);
    second->setValue(sVal);
    total->setValue(fVal + sVal);
}

void FormTotalTime::setRateBtn(double rate)
{
    auto btns = this->findChildren<QRadioButton*>();
    for(auto b : btns){
        if(b->property("rate").toDouble() == rate){
            b->setChecked(true);
            return;
        }
    }
}

void FormTotalTime::setTotal()
{
    int first = m_totalHours.firstTotal();
    int second = m_totalHours.secondTotal();

    ui->sb_totalFirstSemester->setValue(first);
    ui->sb_totalSecondSemester->setValue(second);
    ui->sb_totalYear->setValue(first + second);
}
