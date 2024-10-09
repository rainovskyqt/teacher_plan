#include "roweducationwork.h"
#include "ui_roweducationwork.h"

#include <QDebug>
#include <QComboBox>
#include <QPushButton>

#include <misc/wheelblocker.hpp>

RowEducationWork::RowEducationWork(int position, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RowEducationWork)
{
    ui->setupUi(this);
    setRow(position);

    WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});

    connect(ui->btn_delete, &QPushButton::clicked, this, &RowEducationWork::deleteWork);

    setModels();
}

RowEducationWork::~RowEducationWork()
{
    delete ui;
}

QSize RowEducationWork::rowSize()
{
    return QSize(600, 50);
}

QString RowEducationWork::toString() const
{
    return QString("%1(%2)").arg(
        ui->cb_discipline->currentText(),
        ui->cb_workForm->currentText()
        );
}

int RowEducationWork::id() const
{
    return m_work->id();
}

int RowEducationWork::row() const
{
    return ui->lbl_rowNumber->text().toInt();
}

void RowEducationWork::setRow(int row)
{
    ui->lbl_rowNumber->setNum(row);
}

void RowEducationWork::setModels()
{
    setModel(&m_disciplines, ui->cb_discipline);
    setModel(&m_courses, ui->cb_course);
    setModel(&m_workForm, ui->cb_workForm);
}

void RowEducationWork::setModel(QAbstractItemModel *model, QComboBox *cbox)
{
    cbox->setModel(model);
    cbox->setModelColumn(1);
}

void RowEducationWork::setWorkData(EducationWork *work)
{
    m_work = work;

    setSaved(m_work->id());
    setComboboxData(&m_disciplines, ui->cb_discipline, work->disciplineId());
    setComboboxData(&m_courses, ui->cb_course, work->courseId());
    setComboboxData(&m_workForm, ui->cb_workForm, work->workFormId());
    ui->sb_groupCount->setValue(work->groupCount());
    ui->txt_comments->setPlainText(work->comments());

    connect(ui->cb_discipline, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RowEducationWork::setDiscipline);
    connect(ui->cb_course, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RowEducationWork::setCourse);
    connect(ui->cb_workForm, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RowEducationWork::setWorkForm);
}

void RowEducationWork::setComboboxData(QAbstractItemModel *model, QComboBox *cbox, int vId)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex index = model->index(i, DictionaryModel::Id);
        if (model->data(index).toInt() == vId) {
            cbox->setCurrentIndex(i);
            return;
        }
    }
    cbox->setCurrentIndex(-1);
}

void RowEducationWork::setSaved(bool s)
{
    if(s)
        ui->lbl_rowNumber->setStyleSheet("background-color: rgb(100, 255, 100);");
    else
        ui->lbl_rowNumber->setStyleSheet("background-color: rgb(255, 100, 100);");
}

int RowEducationWork::getDictionaryId(QAbstractItemModel *model, int row)
{
    return model->data(model->index(row, DictionaryModel::Id)).toInt();
}

bool RowEducationWork::checkMainDataForSave()
{
    bool d = ui->cb_discipline->currentIndex() > -1;
    bool c = ui->cb_course->currentIndex() > -1;
    bool w = ui->cb_workForm->currentIndex() > -1;

    if (d && c && w)
        emit saveMainData();
}

void RowEducationWork::setDiscipline(int index)
{
    m_work->setDisciplineId(getDictionaryId(&m_disciplines, index));
}

void RowEducationWork::setCourse(int index)
{
    m_work->setCourseId(getDictionaryId(&m_courses, index));
}

void RowEducationWork::setWorkForm(int index)
{
    m_work->setWorkFormId(getDictionaryId(&m_workForm, index));
}

