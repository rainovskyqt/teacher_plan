#include "educationalworkcomplite.h"
#include "ui_educationalworkcomplite.h"

#include "database/database.h"
#include "database/models/datamodels.h"
#include <QPainter>
#include <misc/month.h>

#define FIRST_SEMESTER_ROW 4
#define SECOND_SEMESTER_ROW 11
#define TOTAL_ROW 12
#define TOTAL_COLUMN 13

void CustomHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
    painter->save();

    QFont font = painter->font();
    //    font.setBold(true);
    painter->setFont(font);

    QString text = model()->headerData(logicalIndex, orientation(), Qt::DisplayRole).toString();

    QTextOption option;
    option.setAlignment(Qt::AlignCenter);
    option.setWrapMode(QTextOption::WordWrap);

    painter->drawText(rect, text, option);

    painter->restore();
}

QSize CustomHeader::sizeHint() const {
    QSize size = QHeaderView::sizeHint();
    QFontMetrics metrics(font());

    for (int i = 0; i < model()->columnCount(); ++i) {
        QString text = model()->headerData(i, orientation(), Qt::DisplayRole).toString();
        QRect rect = metrics.boundingRect(QRect(0, 0, sectionSize(i), 0), Qt::TextWordWrap | Qt::AlignCenter, text);
        size.setHeight(qMax(size.height(), rect.height()));
    }

    return size;
}

EducationalWorkComplite::EducationalWorkComplite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EducationalWorkComplite)
{
    ui->setupUi(this);
    setHeader();
    setColumns();
    setRows();
    fillTable();
}

EducationalWorkComplite::~EducationalWorkComplite()
{
    delete ui;
}

void EducationalWorkComplite::setYearHours(int hours)
{
    QString h = "часов";
    auto remainder = hours % 10;

    switch (remainder) {
    case 1:
        h = "час";
        break;
    case 2:
    case 3:
    case 4:
        h = "часа";
    }

    ui->lbl_yearHours->setText(QString::number(hours));
    ui->lbl_hourText->setText(h);
}

void EducationalWorkComplite::clearHours()
{
    ui->lbl_yearHours->setText("0");
    ui->tw_hours->clearContents();
    fillTable();
}

void EducationalWorkComplite::setFactValue(Month::Months month, int workForm, int value)
{
    int column = getColumnNumber(workForm);
    int row = getRowNumber(month);
    if(row != -1 && column != -1)
        ui->tw_hours->item(row, column)->setText(QString::number(value));
}

void EducationalWorkComplite::setHeader()
{
    CustomHeader *hHeader = new CustomHeader(Qt::Horizontal, ui->tw_hours);
    ui->tw_hours->setHorizontalHeader(hHeader);

    CustomHeader *vHeader = new CustomHeader(Qt::Vertical, ui->tw_hours);
    ui->tw_hours->setVerticalHeader(vHeader);
}

void EducationalWorkComplite::setColumns()
{
    auto workTypes = Database::get()->getDictionary(Database::WorkForm);
    for(int column = 0; column < workTypes.count() - 1; ++column){
        addColumn(workTypes.at(column + 1).name(), workTypes.at(column + 1).id());
    }
    ui->tw_hours->resizeRowsToContents();

    addColumn("Всего\nчасов");
}

void EducationalWorkComplite::addColumn(QString text, int id)
{
    int column = ui->tw_hours->columnCount();
    ui->tw_hours->insertColumn(column);
    auto item = new QTableWidgetItem(text);
    item->setData(Qt::UserRole, id);
    ui->tw_hours->setHorizontalHeaderItem(column, item);
}

void EducationalWorkComplite::setRows()
{
    for(int i = Month::September; i != Month::July; ++i){        //Старт с 9 месяца, так проще
        if(i == Month::Other){
            addRow("Итого за\nсеместр");
            i = Month::January;                //Если перешли за декабрь, ставим январь
        }
        addRow(Month().name((Month::Months)i), i);
    }
    addRow("Итого за\nсеместр");
    addRow("ВСЕГО:");
}

void EducationalWorkComplite::addRow(QString text, int id)
{
    int row = ui->tw_hours->rowCount();
    ui->tw_hours->insertRow(row);
    auto item = new QTableWidgetItem(text);
    item->setData(Qt::UserRole, id);
    ui->tw_hours->setVerticalHeaderItem(row, item);
}

void EducationalWorkComplite::fillTable()
{
    for(int col = 0; col <= ui->tw_hours->columnCount(); ++col){
        for(int row = 0; row <= ui->tw_hours->rowCount(); ++row){
            auto item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            if((col == TOTAL_COLUMN) || (row == FIRST_SEMESTER_ROW) || (row == SECOND_SEMESTER_ROW)){
                item->setBackground(Qt::lightGray);
            } if (row == TOTAL_ROW) {
                item->setBackground(Qt::gray);
            } if ((col == TOTAL_COLUMN && row == FIRST_SEMESTER_ROW) ||
                (col == TOTAL_COLUMN && row == SECOND_SEMESTER_ROW) ||
                (col == TOTAL_COLUMN && row == TOTAL_ROW))
                item->setBackground(Qt::darkGray);
            ui->tw_hours->setItem(row, col, item);
        }
    }
}

int EducationalWorkComplite::getRowNumber(int month)
{
    for(int row = 0; row < ui->tw_hours->rowCount(); ++row){
        auto m =ui->tw_hours->verticalHeaderItem(row)->data(Qt::UserRole).toInt();
        if(m == month)
            return row;
    }
    return -1;
}

int EducationalWorkComplite::getColumnNumber(int workForm)
{
    for(int column = 0; column < ui->tw_hours->columnCount(); ++column){
        auto type = ui->tw_hours->horizontalHeaderItem(column)->data(Qt::UserRole).toInt();
        if(type == workForm)
            return column;
    }
    return -1;
}

void EducationalWorkComplite::setRowCount(int row)
{
    int count = 0;
    for(int i = 0; i < TOTAL_COLUMN; ++i){
        auto item = ui->tw_hours->item(row, i);
        if(item)
            count += item->text().toInt();
    }
    auto item = ui->tw_hours->item(row, TOTAL_COLUMN);
    if(item)
        item->setText(count ? QString::number(count) : "");
}

void EducationalWorkComplite::setColunmCount(int column)
{
    int first = 0;
    int second = 0;

    for(int i = 0; i < TOTAL_ROW; ++i){
        auto item = ui->tw_hours->item(i, column);
        if(!item)
            continue;

        int val = item->text().toInt();

        if(i < FIRST_SEMESTER_ROW){
            first += val;
        } else if (i == FIRST_SEMESTER_ROW){
            item->setText(first ? QString::number(first) : "");
        } else if (i < SECOND_SEMESTER_ROW){
            second += val;
        } else if (i == SECOND_SEMESTER_ROW){
            item->setText(second ? QString::number(second) : "");
        }
    }

    auto item = ui->tw_hours->item(TOTAL_ROW, column);
    if(item){
        int count = first + second;
        item->setText(count ? QString::number(count) : "");
    }
}

void EducationalWorkComplite::checkTotalTime()
{
    auto item = ui->tw_hours->item(TOTAL_ROW, TOTAL_COLUMN);
    if(!item)
        return;

    int totalVal = item->text().toInt();
    int maxTotalVal = ui->lbl_yearHours->text().toInt();
    if(totalVal > maxTotalVal){
        item->setBackground(Qt::red);
    } else if(totalVal == maxTotalVal){
        item->setBackground(Qt::green);
    } else {
        item->setBackground(Qt::darkGray);
    }
}

void EducationalWorkComplite::on_tw_hours_cellChanged(int row, int column)
{
    if(column == TOTAL_COLUMN)
        return;

    setColunmCount(column);
    setRowCount(row);

    checkTotalTime();
}

