#include "pagetitle.h"
#include "pagetotal.h"
#include "printform.h"
#include "ui_printform.h"

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

#include <print/datafiles/printtitledata.h>
#include <print/datafiles/printtotaldata.h>

#define PAGE_WIGTH 210
#define PAGE_HEIGTH 270
#define COEFFICIENT 4

PrintForm::PrintForm(TeacherPlan *plan, User *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PrintForm)
{
    ui->setupUi(this);
    m_plan = plan;
    m_user = user;
}

PrintForm::~PrintForm()
{
    delete ui;
}

void PrintForm::print()
{
    QPrinter *printer = setPrinter();
    QPainter painter;

    // if(!printer)
    //     return;

    // int phys_w = printer->width();
    // int phys_h = printer->height();

    // painter.begin(printer);
    // painter.setWindow(0,0, m_pageWigth, m_pageHeigth);
    // painter.setViewport(0, 0, phys_w, phys_h);

    // painter.end();

    delete printer;
}

QPrinter *PrintForm::setPrinter()
{
    QPrinter *printer = new QPrinter();
    QPrintDialog dialog(printer, this);
    dialog.setWindowTitle("Печать документа");
    if(dialog.exec() != QDialog::Accepted)
        return nullptr;

    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setFullPage(true);
    printer->setOrientation(QPrinter::Portrait);
    printer->setMargins({0,0,0,0});
    printer->setResolution(100);

    return printer;
}

void PrintForm::clearLayout(QLayout *layout) {
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (QWidget *widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    }
}

void PrintForm::on_btn_print_clicked()
{
    print();
}


void PrintForm::on_btn_title_clicked()
{
    clearLayout(ui->vl_printData);

    PrintTitleData *d = new PrintTitleData(this);
    d->setStudyRector("А.М. Безнебеева");
    d->setStartYear(2024);
    d->setEndYear(2025);
    d->setOffice(m_plan->getStaff().depName);
    d->setFio(QString("%1 %2 %3").arg(m_user->userData()->surname(), m_user->userData()->name(), m_user->userData()->middle_name()));
    d->setPost(m_plan->getStaff().postName);


    PageTitle *w = new PageTitle(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, this);
    w->setData(d);
    w->init();
    ui->vl_printData->addWidget(w);
}


void PrintForm::on_btn_total_clicked()
{
    clearLayout(ui->vl_printData);

    PrintTotalData *d = new PrintTotalData(this);
    d->setRate(QString::number(m_plan->rate()));
    emit getTotalTime(d);


    PageTotal *w = new PageTotal(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, this);
    w->setData(d);
    w->init();
    ui->vl_printData->addWidget(w);
}


void PrintForm::on_btn_cancel_clicked()
{
    this->close();
}

