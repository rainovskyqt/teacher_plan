#include "generikworkrow.h"
#include "ui_generikworkrow.h"

#include <QLineEdit>

#include <database/database.h>
#include "database/models/genericworkform.h"

GenerikWorkRow::GenerikWorkRow(GenericWork *work, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GenerikWorkRow)
{
    ui->setupUi(this);
    m_work = work;
    loadWorks();
}

GenerikWorkRow::~GenerikWorkRow()
{
    delete ui;
}

void GenerikWorkRow::loadWorks()
{
    auto works = Database::get()->getWorks(m_work->type());
    for(auto w: works){
        ui->cb_works->addItem(w->fullName(), w->baseId());
    }
}
