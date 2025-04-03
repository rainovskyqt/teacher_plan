#include "pageanalysis.h"
#include "pagecomplete.h"
#include "pagetitle.h"
#include "pagetotal.h"
#include "printform.h"
#include "ui_printform.h"

#include <QPrintDialog>
#include <QPainter>

#include <print/datafiles/printtitledata.h>
#include <print/datafiles/printtotaldata.h>
#include <print/datafiles/printanalysisdata.h>
#include <print/datafiles/printgenericwork.h>

#include "genericworks/pagemethodicwork.h"

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
    ui->w_semester->setVisible(false);
}

PrintForm::~PrintForm()
{
    delete ui;
}

void PrintForm::print()
{
    QPrinter *printer = setPrinter(getOrientation());

    if(!printer)
        return;

    PrintPage *p = qobject_cast<PrintPage*>(ui->vl_printData->itemAt(0)->widget());
    p->print(printer);

    delete printer;
}

QPrinter *PrintForm::setPrinter(QPrinter::Orientation o)
{
    QPrinter *printer = new QPrinter();
    QPrintDialog dialog(printer, this);
    dialog.setWindowTitle("Печать документа");
    if(dialog.exec() != QDialog::Accepted)
        return nullptr;

    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setFullPage(true);
    printer->setOrientation(o);
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

void PrintForm::setSemester()
{
    auto currentWidget = ui->vl_printData->itemAt(0)->widget();
    if(qobject_cast<PageAnalysis*>(currentWidget)){
        on_btn_analisis_clicked();
    } else if(qobject_cast<PageMethodicWork*>(currentWidget)){
        on_btn_workMethodic_clicked();
    }

}

void PrintForm::on_btn_print_clicked()
{
    print();
}


void PrintForm::on_btn_title_clicked()
{
    ui->w_semester->setVisible(false);
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
    ui->w_semester->setVisible(false);
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


void PrintForm::on_btn_analisis_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintAnalysisData *ad = new PrintAnalysisData(this);
    ad->setSecondSemester(ui->rb_second->isChecked());

    PageAnalysis *w = new PageAnalysis(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, this);
    w->setData(ad);
    w->init();
    ui->vl_printData->addWidget(w);
}


void PrintForm::on_rb_first_clicked()
{
    setSemester();
}


void PrintForm::on_rb_second_clicked()
{
    setSemester();
}

QPrinter::Orientation PrintForm::getOrientation()
{
    QPrinter::Orientation o = QPrinter::Portrait;

    auto currentWidget = ui->vl_printData->itemAt(0)->widget();
    if(qobject_cast<PageComplete*>(currentWidget)){
                o = QPrinter::Landscape;
    }

    return o;
}


void PrintForm::on_btn_complete_clicked()
{
    ui->w_semester->setVisible(false);
    clearLayout(ui->vl_printData);

    PrintComplite *pc = new PrintComplite(this);
    pc->setComments(m_plan->comments());
    emit getCompliteTime(pc);

    PageComplete *w = new PageComplete(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, this); //При горизонтальной ориентации меняем ширину и высоту местами
    w->setData(pc);
    w->init();
    ui->vl_printData->addWidget(w);
}


void PrintForm::on_btn_workMethodic_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintGenericWork *gd = new PrintGenericWork(this);
    gd->setApprovedPost("Проректор по научно-исследовательской\n"
                        "работе ФГБОУ ВО \"ВГАФК\"");
    gd->setApprovedUser("И.А. Фатьянов");
    gd->setSecondSemester(ui->rb_second->isChecked());
    // emit getCompliteTime(pc);

    PageMethodicWork *w = new PageMethodicWork(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, this);
    w->setData(gd);
    w->init();
    ui->vl_printData->addWidget(w);
}

