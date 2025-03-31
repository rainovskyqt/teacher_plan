#include "educationalworkcomplite.h"
#include "ui_educationalworkcomplite.h"

#include "database/database.h"
#include "database/models/datamodels.h"
#include <QPainter>
#include <misc/month.h>

#define FIRST_SEMESTER_ROW 5
#define SECOND_SEMESTER_ROW 11
#define TOTAL_ROW 12
#define TOTAL_COLUMN 16

void CustomHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
    painter->save();

    QFont font = painter->font();
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
    ui(new Ui::EducationalWorkComplite),
    m_planId{0}
{
    ui->setupUi(this);
    setHeader();
    setColumns();
    setRows();
    fillTable();

    connect(ui->tw_hours, &QTableWidget::cellChanged, this, &EducationalWorkComplite::hoursChanged);
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
        ui->tw_hours->item(row, column)->setText(value ? QString::number(value) : "");
}

void EducationalWorkComplite::setMonthValue(Month::Months month, int workForm, int value, EducationalHour::HourType hourType)
{
    int column = getColumnNumber(workForm);
    int row = getRowNumber(month);
    if(row != -1 && column != -1){
        auto item = ui->tw_hours->item(row, column);
        if(hourType == EducationalHour::HourType::Plane)
            item->setData(Plane, value);
        else
            item->setData(Factical, value);
        item->setText(QString("%1 / %2").arg(item->data(Plane).toString(), item->data(Factical).toString()));
    }
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
    for(int column = 0; column < workTypes.count(); ++column){
        addColumn(workTypes.at(column).name(), workTypes.at(column).id());
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
            i = Month::January;                //Если перешли за декабрь, ставим январь
        }
        addRow(Month().name((Month::Months)i), i);
        if(i == Month::January){
            addRow("Итого за\nсеместр");
        }
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
    for(int col = 0; col <= TOTAL_COLUMN; ++col){
        for(int row = 0; row <= TOTAL_ROW; ++row){
            auto item = new QTableWidgetItem("");
            item->setData(Plane, 0);
            item->setData(Factical, 0);
            item->setTextAlignment(Qt::AlignCenter);

            if (col == TOTAL_COLUMN && (row == FIRST_SEMESTER_ROW || row == SECOND_SEMESTER_ROW || row == TOTAL_ROW)){
                item->setBackground(Qt::darkGray);
            } else if(col == TOTAL_COLUMN || row == FIRST_SEMESTER_ROW || row == SECOND_SEMESTER_ROW){
                item->setBackground(Qt::lightGray);
            } else if (row == TOTAL_ROW) {
                item->setBackground(Qt::gray);
            }
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
    int countPlane = 0;
    int countFact = 0;
    for(int i = 0; i < TOTAL_COLUMN; ++i){
        auto item = ui->tw_hours->item(row, i);
        if(item){
            countPlane += item->data(Plane).toInt();
            countFact += item->data(Factical).toInt();
        }
    }
    auto item = ui->tw_hours->item(row, TOTAL_COLUMN);
    if(item != nullptr)
        item->setText((countPlane || countFact) ? QString("%1 / %2").arg(countPlane).arg(countFact) : "");
}

void EducationalWorkComplite::setColunmCount(int column)
{
    int firstPlane = 0;
    int firstFact = 0;
    int secondPlane = 0;
    int secondFact = 0;

    for(int i = 0; i < TOTAL_ROW; ++i){
        auto item = ui->tw_hours->item(i, column);
        if(!item)
            continue;

        if(i < FIRST_SEMESTER_ROW){
            firstPlane += item->data(Plane).toInt();
            firstFact += item->data(Factical).toInt();
        } else if (i == FIRST_SEMESTER_ROW){
            item->setText((firstPlane || firstFact) ? QString("%1 / %2").arg(firstPlane).arg(firstFact) : "");
            qDebug() << firstPlane <<"   " << i <<"   " << column;
            item->setData(Plane, firstPlane);
            item->setData(Factical, firstFact);
        } else if (i < SECOND_SEMESTER_ROW){
            secondPlane += item->data(Plane).toInt();
            secondFact += item->data(Factical).toInt();
        } else if (i == SECOND_SEMESTER_ROW){
            item->setData(Plane, secondPlane);
            item->setData(Factical, secondFact);
            item->setText((secondPlane || secondFact) ? QString("%1 / %2").arg(secondPlane).arg(secondFact) : "");
        }
    }

    auto item = ui->tw_hours->item(TOTAL_ROW, column);
    if(item){
        int countPlane = firstPlane + secondPlane;
        int countFact = firstFact + secondFact;
        item->setData(Plane, countPlane);
        item->setData(Factical, countFact);
        item->setText((countPlane || countFact) ? QString("%1 / %2").arg(countPlane).arg(countFact) : "");
    }
}

void EducationalWorkComplite::setYearCount()
{

}

void EducationalWorkComplite::checkTotalTime()
{
    auto item = ui->tw_hours->item(TOTAL_ROW, TOTAL_COLUMN);
    if(!item)
        return;

    int totalVal = item->data(Plane).toInt();
    int maxTotalVal = ui->lbl_yearHours->text().toInt();
    if(totalVal > maxTotalVal){
        item->setBackground(Qt::red);
    } else if(totalVal == maxTotalVal){
        item->setBackground(Qt::green);
    } else {
        item->setBackground(Qt::darkGray);
    }
}

void EducationalWorkComplite::setComments()
{
    ui->text_comments->setPlainText(Database::get()->getTeacherPlanComments(m_planId));
}

void EducationalWorkComplite::hoursChanged(int row, int column)
{
    if(column != TOTAL_COLUMN)
        setColunmCount(column);

    setRowCount(row);
    checkTotalTime();
}

int EducationalWorkComplite::planId() const
{
    return m_planId;
}

void EducationalWorkComplite::setPlanId(int newPlanId)
{
    m_planId = newPlanId;
    setComments();
}

void EducationalWorkComplite::setCompliteTime(PrintComplite *c)
{
    for(int row = 0; row < ui->tw_hours->rowCount(); ++row){
        for(int column = 0; column < ui->tw_hours->columnCount(); ++column){
            c->setValue(row, column, ui->tw_hours->item(row, column)->text());
        }
    }
}

void EducationalWorkComplite::on_text_comments_textChanged()
{
    Database::get()->updateTeacherPlanComments(m_planId, ui->text_comments->toPlainText());
}

