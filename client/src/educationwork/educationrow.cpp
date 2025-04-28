#include "educationmonth.h"
#include "educationrow.h"
#include "educationmonth.h"
#include "ui_educationrow.h"

#include <QDebug>
#include <QPushButton>

#include "database/models/educationalwork.h"
#include <database/database.h>
#include <database/adapters/dictionaryadapter.h>

#include <misc/month.h>
#include <settings.h>
#include <QScrollBar>
#include "misc/wheelblocker.hpp"

// Для простановки часов используется QLineEdit что бы были пустые места, если буду QSpinBox, то будут 0, и форма будет перегружена


EducationRow::EducationRow(int row, EducationalWork *work, S status, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationRow)
    ,m_work(nullptr)
{
    readySave = false;
    ui->setupUi(this);
    setRow(row);
    loadDictionaries();
    setData(work);
    setStatus(status);
    addMonths(status);
    makeConnections();
    WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});
}

EducationRow::~EducationRow()
{
    delete ui;
}

void EducationRow::addMonths(S status)
{
    bool planReadOnly = !(status == S::Development);
    bool factReadOnly = !(status == S::Development || status == S::Aproved);

    int startWeek = 1;
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other)
            i = Month::January;                //Если перешли за декабрь, ставим январь
        int weekCount = Settings::get().weekCount((Month::Months)i);

        auto workId = 0;
        if(m_work)
            workId = m_work->baseId();

        auto month = new EducationMonth((Month::Months)i, startWeek, weekCount, workId, planReadOnly, factReadOnly);
        connect(month, &EducationMonth::hoursChanged, this, [&](EducationalHour *hour){
            countHours(hour->type());
            saveHour(hour);
            emit valueChanged(hour);

            // if(hour->type() == EducationalHour::Factical){
            auto month = static_cast<EducationMonth*>(sender());
            int factCount = month->getTime(hour->type());
            // int factCount = month->getTime( EducationalHour::Factical);
            emit factValueChanged(month->month(), m_work->workFormId(), factCount, hour->type());
            // }
        });
        ui->hl_months->addWidget(month);
        startWeek += weekCount;
    }
}

void EducationRow::setData(EducationalWork *work)
{
    m_work = work;
    ui->text_comments->setPlainText(work->comments());
    ui->cb_discipline->setCurrentIndex(ui->cb_discipline->findData(m_work->disciplineId()));
    ui->cb_course->setCurrentIndex(ui->cb_course->findData(m_work->courseId()));
    ui->cb_workForm->setCurrentIndex(ui->cb_workForm->findData(m_work->workFormId()));
    ui->sb_groupCount->setValue(work->groupCount());
    colorRow((bool)m_work->baseId());
}

QString EducationRow::toString()
{
    return QString("%1(%2)").arg(
        ui->cb_discipline->currentText(),
        ui->cb_workForm->currentText()
        );
}

void EducationRow::countHours(EducationalHour::HourType type)
{
    int firstCount = 0;
    int secontCount = 0;
    auto month = this->findChildren<EducationMonth*>();
    for(auto m: month){
        if(m->isFirstSemester())
            firstCount += m->getTime(type);
        else
            secontCount += m->getTime(type);
    }
    if(type == EducationalHour::Plane){
        ui->lbl_firstPlan->setText(QString::number(firstCount));
        ui->lbl_secondPlan->setText(QString::number(secontCount));
        ui->lbl_yearPlan->setText(QString::number(firstCount + secontCount));
    } else {
        ui->lbl_firstFact->setText(QString::number(firstCount));
        ui->lbl_secondFact->setText(QString::number(secontCount));
        ui->lbl_yearFact->setText(QString::number(firstCount + secontCount));
    }
}

void EducationRow::setStatus(S status)
{
    m_status = status;

    ui->cb_discipline->setEnabled(status == S::Development);
    ui->cb_course->setEnabled(status == S::Development);
    ui->cb_workForm->setEnabled(status == S::Development);
    ui->btn_deleteRow->setEnabled(status == S::Development);

    ui->sb_groupCount->setReadOnly(status != S::Development);
}

EducationalWork *EducationRow::work() const
{
    return m_work;
}

int EducationRow::getTime(EducationalHour::HourType type, int week)
{
    auto month = this->findChildren<EducationMonth*>();
    int count = 0;
    for(auto m: month){
        count += m->getTime(type, week);
    }
    return count;
}

void EducationRow::loadHours()
{
    auto hours = Database::get()->getEdcationalHours(m_work->baseId());
    auto month = this->findChildren<EducationMonth*>();

    for(auto m: month){
        for(auto h: hours)
            m->setValue(h);
    }

    readySave = true;
}

int EducationRow::row()
{
    return ui->lbl_number->text().toInt();
}

void EducationRow::setRow(int row)
{
    ui->lbl_number->setText(QString::number(row));
}

int EducationRow::totalPlaneI() const
{
    return ui->lbl_firstPlan->text().toInt();
}

int EducationRow::totalFactI() const
{
    return ui->lbl_firstFact->text().toInt();
}

int EducationRow::totalPlaneII() const
{
    return ui->lbl_secondPlan->text().toInt();
}

int EducationRow::totalFactII() const
{
    return ui->lbl_secondFact->text().toInt();
}

int EducationRow::totalPlaneYear() const
{
    return ui->lbl_yearPlan->text().toInt();
}

int EducationRow::totalFactYear() const
{
    return ui->lbl_yearFact->text().toInt();
}

QString EducationRow::comments()
{
    return ui->text_comments->toPlainText();
}

int EducationRow::countMonthHourse(Month::Months month, EducationalHour::HourType type)
{
    int count = 0;
    auto months = this->findChildren<EducationMonth*>();
    for(auto m: months){
        if(m->month() == month)
            count += m->getTime(type);
    }
    return count;
}

int EducationRow::workForm()
{
    return m_work->workFormId();
}

QString EducationRow::name() const
{
    return QString("%1/%2/%3").arg(ui->cb_discipline->currentText(), ui->cb_course->currentText(), ui->cb_workForm->currentText());
}

QPair<bool, QPair<int, int>> EducationRow::weekHours(int week)
{
    auto month = this->findChildren<EducationMonth*>();
    for(auto m: month){
        auto wh = m->weekHours(week);
        if(wh.first){
            return wh;
        }
    }
    return qMakePair(false, qMakePair(-1,-1));
}

void EducationRow::setScrolBarValue(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void EducationRow::loadDictionaries()
{
    DictionaryAdapter::setDictionary(ui->cb_discipline, Database::Discipline);
    ui->cb_discipline->setCurrentIndex(0);
    DictionaryAdapter::setDictionary(ui->cb_course, Database::Course);
    ui->cb_course->setCurrentIndex(0);
    DictionaryAdapter::setDictionary(ui->cb_workForm, Database::WorkForm);
    ui->cb_workForm->setCurrentIndex(0);
}

void EducationRow::makeConnections()
{
    connect(ui->cb_discipline, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setDisciplineId(ui->cb_discipline->currentData().toInt());
        colorRow(Database::get()->saveWork(m_work));
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->cb_course, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setCourseId(ui->cb_course->currentData().toInt());
        colorRow(Database::get()->saveWork(m_work));
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->cb_workForm, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setWorkFormId(ui->cb_workForm->currentData().toInt());
        colorRow(Database::get()->saveWork(m_work));
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->sb_groupCount, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int val){
        m_work->setGroupCount(val);
        colorRow(Database::get()->saveWork(m_work));
    });

    connect(ui->text_comments, &QPlainTextEdit::textChanged, this, [&]{
        m_work->setComments(ui->text_comments->toPlainText());
        colorRow(Database::get()->saveWork(m_work));
    });

    connect(ui->btn_deleteRow, &QPushButton::clicked, this, &EducationRow::deleteWork);

}

void EducationRow::saveHour(EducationalHour *hour)
{
    if(readySave)
        Database::get()->saveEdcationalHour(hour);
}

void EducationRow::setNewWorkId(int id)
{
    auto month = this->findChildren<EducationMonth*>();

    for(auto m: month){
        m->setNewWorkId(id);
    }
}

void EducationRow::colorRow(bool accepted)
{
    if(accepted)
        ui->lbl_number->setStyleSheet("background-color: rgb(100, 255, 100);");
    else
        ui->lbl_number->setStyleSheet("background-color: rgb(255, 100, 100);");
}
