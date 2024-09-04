#include "generikworkrow.h"
#include "ui_generikworkrow.h"

#include <QLineEdit>
#include <QPushButton>

#include <database/database.h>
#include "database/models/genericworkform.h"

GenerikWorkRow::GenerikWorkRow(GenericWork *work, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenerikWorkRow)
{
    ui->setupUi(this);
    m_work = work;
    loadWorks();

    connect(ui->line_plan, &QLineEdit::textEdited, this, [&]{
        emit valueChanged();
    });
    connect(ui->line_fact, &QLineEdit::textEdited, this, [&]{
        emit valueChanged();
    });

    connect(ui->btn_delete, &QPushButton::clicked, this, &GenerikWorkRow::deleteWork);
}

GenerikWorkRow::~GenerikWorkRow()
{
    delete ui;
}

int GenerikWorkRow::planeHours()
{
    return ui->line_plan->text().toInt();
}

int GenerikWorkRow::factHours()
{
    return ui->line_fact->text().toInt();
}

QString GenerikWorkRow::toString()
{
    return QString("%1(%2)").arg(
        ui->cb_works->currentText()
        );
}

void GenerikWorkRow::loadWorks()
{
    auto works = Database::get()->getWorks(m_work->type());
    for(auto w: works){
        ui->cb_works->addItem(w->fullName(), w->baseId());
    }
}

GenericWork *GenerikWorkRow::work() const
{
    return m_work;
}
