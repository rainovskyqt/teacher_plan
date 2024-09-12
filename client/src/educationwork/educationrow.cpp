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

// Для простановки часов используется QLineEdit что бы были пустые места, если буду QSpinBox, то будут 0, и форма будет перегружена

EducationRow::EducationRow(int row, EducationalWork *work, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationRow)
    ,m_work(nullptr)
{
    readySave = false;
    ui->setupUi(this);
    ui->lbl_number->setText(QString::number(row));
    loadDictionaries();
    setData(work);
    addMonths();
    makeConnections();
}

EducationRow::~EducationRow()
{
    delete ui;
}

void EducationRow::addMonths()
{
    int startWeek = 1;
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other)
            i = Month::January;                //Если перешли за декабрь, ставим январь
        int weekCount = Settings::get().weekCount((Month::Months)i);

        auto workId = 0;
        if(m_work)
            workId = m_work->baseId();

        auto month = new EducationMonth((Month::Months)i, startWeek, weekCount, workId, false, this);
        connect(month, &EducationMonth::hoursChanged, this, [&](EducationalHour *hour){
            countHours(hour->type());
            saveHour(hour);
            emit valueChanged(hour);

            if(hour->type() == EducationalHour::Factical){
                auto month = static_cast<EducationMonth*>(sender());
                int factCount = month->getTime(EducationalHour::Factical);
                emit factValueChanged(month->month(), m_work->workFormId(), factCount);
            }
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

int EducationRow::timeAreaWidth()
{
    return ui->scrollArea->horizontalScrollBar()->maximum() +
           ui->text_comments->width() +
           ui->lbl_firstPlan->width() +
           ui->lbl_secondPlan->width() +
           ui->lbl_yearPlan->width();
}

void EducationRow::setScrolBarValue(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void EducationRow::loadDictionaries()
{
    DictionaryAdapter::setDictionary(ui->cb_discipline, Database::Discipline);
    DictionaryAdapter::setDictionary(ui->cb_course, Database::Course);
    DictionaryAdapter::setDictionary(ui->cb_workForm, Database::WorkForm);
}

void EducationRow::makeConnections()
{
    connect(ui->cb_discipline, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setDisciplineId(ui->cb_discipline->currentData().toInt());
        Database::get()->saveWork(m_work);
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->cb_course, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setCourseId(ui->cb_course->currentData().toInt());
        Database::get()->saveWork(m_work);
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->cb_workForm, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        int oldId = m_work->baseId();
        m_work->setWorkFormId(ui->cb_workForm->currentData().toInt());
        Database::get()->saveWork(m_work);
        if(oldId != m_work->baseId())
            setNewWorkId(m_work->baseId());
    });

    connect(ui->sb_groupCount, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int val){
        m_work->setGroupCount(val);
        Database::get()->saveWork(m_work);
    });

    connect(ui->text_comments, &QPlainTextEdit::textChanged, this, [&]{
        m_work->setComments(ui->text_comments->toPlainText());
        Database::get()->saveWork(m_work);
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
