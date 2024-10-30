#include "generikworkrow.h"
#include "ui_generikworkrow.h"

#include <QSpinBox>
#include <QPushButton>
#include <QPlainTextEdit>

#include <database/database.h>

#include <database/dictionary/dictionarymanager.h>

GenerikWorkRow::GenerikWorkRow(GenericWork *work, int number, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenerikWorkRow)
{
    ui->setupUi(this);

    m_workForms.setSourceModel(DictionaryManager::get()->genericWorkForm());
    m_workForms.setFilterKeyColumn(DictionaryModel::WorkType);
    m_workForms.setFilterFixedString(QString::number((int)work->workType()));
    ui->cb_works->setModel(&m_workForms);
    ui->cb_works->setModelColumn(DictionaryModel::Name);
    ui->lbl_number->setNum(number);
    ui->cb_works->setCurrentIndex(-1);
    setWorkData(work);
}

GenerikWorkRow::~GenerikWorkRow()
{
    delete ui;
}

// int GenerikWorkRow::planeHours()
// {
//     return ui->sb_plan->value();
// }

// int GenerikWorkRow::factHours()
// {
//     return ui->sb_fact->value();
// }

QString GenerikWorkRow::toString()
{
    return QString("%1(%2)").arg(
        ui->cb_works->currentText()
        );
}

void GenerikWorkRow::setWorkData(GenericWork *work)
{
    m_work = work;

    if(!m_work->id()){
        colorRow(false);
        return;
    }
    setComboboxData(&m_workForms, ui->cb_works, work->workFormId());
    ui->sb_plan->setValue(m_work->planHours());
    ui->sb_fact->setValue(m_work->factHours());
    ui->text_complite->setPlainText(m_work->complite());

    // emit valueChanged();
}

void GenerikWorkRow::setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId)
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

// GenericWork *GenerikWorkRow::work() const
// {
//     return m_work;
// }

// void GenerikWorkRow::init()
// {
//     loadWorkTypes();
//     setWorkData(m_work);
//     makeConnections();
// }

// void GenerikWorkRow::makeConnections()
// {
//     connect(ui->cb_works, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&]{
//         m_work->setWorkFormId(ui->cb_works->currentData().toInt());
//         colorRow(Database::get()->saveWork(m_work));
//     });

//     connect(ui->sb_plan, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int val){
//         m_work->setPlanHours(val);
//         colorRow(Database::get()->saveWork(m_work));
//         emit valueChanged();
//     });

//     connect(ui->sb_fact, QOverload<int>::of(&QSpinBox::valueChanged), this, [&](int val){
//         m_work->setFactHours(val);
//         colorRow(Database::get()->saveWork(m_work));
//         emit valueChanged();
//     });

//     connect(ui->text_complite, &QPlainTextEdit::textChanged, this, [&](){
//         auto text = static_cast<QPlainTextEdit*>(sender());
//         m_work->setComplite(text->toPlainText());
//         colorRow(Database::get()->saveWork(m_work));
//         emit valueChanged();
//     });

//     connect(ui->btn_delete, &QPushButton::clicked, this, &GenerikWorkRow::deleteWork);
// }

void GenerikWorkRow::colorRow(bool accepted)
{
    if(accepted)
        ui->lbl_number->setStyleSheet("background-color: rgb(100, 255, 100);");
    else
        ui->lbl_number->setStyleSheet("background-color: rgb(255, 100, 100);");
}
