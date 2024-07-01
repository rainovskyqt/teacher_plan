#include "educationrow.h"
#include "ui_educationrow.h"

#include <QDebug>

#include "database/models/educationalwork.h"
#include <database/database.h>
#include <database/adapters/dictionaryadapter.h>

// Для простановки часов используется QLineEdit что бы были пустые места, если буду QSpinBox, то будут 0, и форма будет перегружена

EducationRow::EducationRow(int row, EducationalWork *work, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationRow)
{
    ui->setupUi(this);
    ui->lbl_number->setText(QString::number(row));
    loadDictionaries();
    setData(work);
    makeConnections();
    makeHoursConnections();
}

EducationRow::~EducationRow()
{
    delete ui;
}

void EducationRow::setData(EducationalWork *work)
{
    m_work = work;
    ui->text_comments->setPlainText(work->comments());
    ui->cb_discipline->setCurrentIndex(ui->cb_discipline->findData(m_work->disciplineId()));
    ui->cb_group->setCurrentIndex(ui->cb_group->findData(m_work->groupId()));
    ui->cb_workForm->setCurrentIndex(ui->cb_workForm->findData(m_work->workFormId()));
}

QString EducationRow::toString()
{
    return ui->cb_discipline->currentText();
}

EducationalWork *EducationRow::work() const
{
    return m_work;
}

void EducationRow::on_btn_deleteRow_clicked()
{
    emit deleteWork();
}

void EducationRow::countHours()
{
    auto name = sender()->objectName();
    if(name.contains("f"))
        countFacticalHours();
    else if(name.contains("p"))
        countPlanHours();
}

void EducationRow::countPlanHours()
{
    int firstValue = 0;
    int secondValue = 0;
    auto lines = this->findChildren<QLineEdit*>(QRegExp("\\b\\w*p\\w*\\b"));
    foreach (auto c, lines) {
        auto name = c->objectName();
        if(name.contains(QRegExp("\\b\\w*m(9|10|11|12)\\w*\\b")))
            firstValue += c->text().toInt();
        else if (name.contains(QRegExp("\\b\\w*m(1|2|3|4|5|6)\\w*\\b")))
            secondValue += c->text().toInt();
    }
    ui->lbl_firstPlan->setText(QString::number(firstValue));
    ui->lbl_secondPlan->setText(QString::number(secondValue));
    countYearPlan();
}

void EducationRow::countFacticalHours()
{
    int firstValue = 0;
    int secondValue = 0;
    auto lines = this->findChildren<QLineEdit*>(QRegExp("\\b\\w*f\\w*\\b"));
    foreach (auto c, lines) {
        auto name = c->objectName();
        if(name.contains(QRegExp("\\b\\w*m(9|10|11|12)\\w*\\b")))
            firstValue += c->text().toInt();
        else if (name.contains(QRegExp("\\b\\w*m(1|2|3|4|5|6)\\w*\\b")))
            secondValue += c->text().toInt();
    }
    ui->lbl_firstFact->setText(QString::number(firstValue));
    ui->lbl_secondFact->setText(QString::number(secondValue));
    countYearFactical();
}

void EducationRow::countYearPlan()
{
    ui->lbl_yearPlan->setText(QString::number(ui->lbl_firstPlan->text().toInt() + ui->lbl_secondPlan->text().toInt()));
}

void EducationRow::countYearFactical()
{
    ui->lbl_yearFact->setText(QString::number(ui->lbl_firstFact->text().toInt() + ui->lbl_secondFact->text().toInt()));
}

void EducationRow::loadDictionaries()
{
    DictionaryAdapter::setDictionary(ui->cb_discipline, Database::Discipline);
    DictionaryAdapter::setDictionary(ui->cb_group, Database::Group);
    DictionaryAdapter::setDictionary(ui->cb_workForm, Database::WorkForm);
}

void EducationRow::makeConnections()
{
    connect(ui->cb_discipline, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        work()->setDisciplineId(ui->cb_discipline->currentData().toInt());
        emit saveWork(m_work);
    });

    connect(ui->cb_group, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        work()->setGroupId(ui->cb_group->currentData().toInt());
         emit saveWork(m_work);
    });

    connect(ui->cb_workForm, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
        work()->setWorkFormId(ui->cb_workForm->currentData().toInt());
         emit saveWork(m_work);
    });

    connect(ui->text_comments, &QPlainTextEdit::textChanged, this, [&]{
        work()->setComments(ui->text_comments->toPlainText());
        emit saveWork(m_work);
    });
}

void EducationRow::makeHoursConnections()
{
    foreach (auto c, this->findChildren<QLineEdit*>()) {
        connect(c, &QLineEdit::textChanged, this, &EducationRow::countHours);
    }
}
