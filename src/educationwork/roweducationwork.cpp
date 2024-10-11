#include "roweducationwork.h"
#include "ui_roweducationwork.h"

#include <QDebug>
#include <QComboBox>
#include <QPushButton>

#include <misc/wheelblocker.hpp>
#include "database/dictionary/dictionarymanager.h"

RowEducationWork::RowEducationWork(int position, const ModelEducationWork::EducationWork &work,
                                   Position pos, bool enabled, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RowEducationWork)
{
    ui->setupUi(this);

    if(setRow(pos)){
        setRow(position);

        WheelBlocker::make({ui->cb_course, ui->cb_discipline, ui->cb_workForm, ui->sb_groupCount});

        connect(ui->btn_delete, &QPushButton::clicked, this, &RowEducationWork::deleteWork);

        setModels();
        setWorkData(work);
        setEnabled(enabled);
    }
}

RowEducationWork::~RowEducationWork()
{
    delete ui;
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
    return m_work.id;
}

int RowEducationWork::row() const
{
    return ui->lbl_rowNumber->text().toInt();
}

void RowEducationWork::setRow(int row)
{
    ui->lbl_rowNumber->setNum(row);
}

ModelEducationWork::EducationWork RowEducationWork::work() const
{
    return m_work;
}

void RowEducationWork::setModels()
{
    setModel(DictionaryManager::get()->disciplines(), &m_disciplines, ui->cb_discipline);
    setModel(DictionaryManager::get()->courses(),&m_courses, ui->cb_course);
    setModel(DictionaryManager::get()->workForm(),&m_workForm, ui->cb_workForm);
}

void RowEducationWork::setModel(QAbstractItemModel *model, QSortFilterProxyModel *proxy, QComboBox *cbox)
{
    proxy->setSourceModel(model);
    cbox->setModel(proxy);
    cbox->setModelColumn(DictionaryModel::Name);
}

void RowEducationWork::setWorkData(const ModelEducationWork::EducationWork &work)
{
    m_work = work;

    setSaved(m_work.id);
    setComboboxData(&m_disciplines, ui->cb_discipline, work.disciplineId);
    setComboboxData(&m_courses, ui->cb_course, work.courseId);
    setComboboxData(&m_workForm, ui->cb_workForm, work.workFormId);
    ui->sb_groupCount->setValue(work.groupCount);    
    ui->txt_comments->setPlainText(work.comments);
}

void RowEducationWork::setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QModelIndex index = model->index(i, DictionaryModel::Id);
        if (model->data(index).toInt() == vId) {
            cbox->setCurrentIndex(index.row());
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

bool RowEducationWork::setRow(Position pos)
{
    ui->sw_comboboxes->setCurrentIndex((int)pos);
    ui->sw_hourTypeLbl->setCurrentIndex((int)pos);
    ui->sw_comments->setCurrentIndex((int)pos);
    ui->sw_total->setCurrentIndex((int)pos);

    return pos == Position::Row;
}
