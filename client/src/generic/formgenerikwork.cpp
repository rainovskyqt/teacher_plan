#include "formgenerikwork.h"
#include "ui_formgenerikwork.h"

#include <QScrollBar>

#include <database/models/genericwork.h>
#include "generic/generikworkrow.h"

FormGenerikWork::FormGenerikWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormGenerikWork)
{
    ui->setupUi(this);
    setConnections();
}

FormGenerikWork::~FormGenerikWork()
{
    delete ui;
}

void FormGenerikWork::setConnections()
{
    // connect(ui->lw_educationWork->horizontalScrollBar(), &QScrollBar::valueChanged,
    //         ui->w_edHeader, &EducationHeader::setPosition);

    connect(ui->lw_first->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_footerFirst, &GenericFooter::setPosition);
    connect(ui->lw_second->horizontalScrollBar(), &QScrollBar::valueChanged,
            ui->w_footerSecond, &GenericFooter::setPosition);
}

void FormGenerikWork::addRow(GenericWork *work)
{
    auto list = currentList();
    auto item = new QListWidgetItem(list);
    auto row = new GenerikWorkRow(work);
    item->setSizeHint(row->sizeHint());
    list->setItemWidget(item, row);
    // connect(row, &EducationRow::deleteWork, this, &FormEducationWork::deleteRow);
    // Database::get()->saveWork(work);

    // connect(row, &EducationRow::valueChanget, this, [this](QString line){
    //     ui->w_footer->setValue(countHours(line), line);
    // });

    // connect(row, &EducationRow::totalValueChanget, this, [this](QString lbl){
    //     ui->w_footer->setTotalValue(countTotalHours(lbl), lbl);
    // });
}

QListWidget *FormGenerikWork::currentList()
{
    if(ui->tabWidget->currentIndex() == 0)
        return ui->lw_first;
    else
        return ui->lw_second;
}

void FormGenerikWork::on_btn_add_clicked()
{
    addRow(new GenericWork(WorkType::MethodicWork));
}

