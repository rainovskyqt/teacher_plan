#include "pageanalysis.h"
#include "pagecomplete.h"
#include "pagestudy.h"
#include "pagetitle.h"
#include "pagetotal.h"
#include "printform.h"
#include "ui_printform.h"

#include <QPrintDialog>
#include <QPainter>

#include <print/datafiles/printtitledata.h>
#include <print/datafiles/printtotaldata.h>
#include <print/datafiles/printanalysisdata.h>
#include <print/datafiles/printstudydata.h>

#include "genericworks/pagemethodicwork.h"
#include "genericworks/pageotherwork.h"
#include "genericworks/pageresearchingwork.h"
#include "genericworks/pagesportwork.h"

#define PAGE_WIGTH 210
#define PAGE_HEIGTH 297
#define COEFFICIENT 4
#define MAX_ROW_COUNT 25

using PP = PrintPage::PagePosition;

PrintForm::PrintForm(TeacherPlan *plan, User *user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PrintForm)
{
    ui->setupUi(this);
    m_plan = plan;
    m_user = user;
    ui->w_semester->setVisible(false);
    on_btn_title_clicked();
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

    for(int i = 0; i < ui->vl_printData->count(); ++i){
        PrintPage *p = qobject_cast<PrintPage*>(ui->vl_printData->itemAt(i)->widget());
        p->print(printer);
    }

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
    } else if(qobject_cast<PageResearchingWork*>(currentWidget)){
        on_btn_researchingWork_clicked();
    } else if(qobject_cast<PageSportWork*>(currentWidget)){
        on_btn_sportWork_clicked();
    } else if(qobject_cast<PageOtherWork*>(currentWidget)){
        on_btn_otherWork_clicked();
    } else if(qobject_cast<PageStudy*>(currentWidget)){
        on_btn_workStudy_clicked();
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


    PageTitle *w = new PageTitle(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, PP::Single, 0, this);
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


    PageTotal *w = new PageTotal(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, PP::Single, 0, this);
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

    PageAnalysis *w = new PageAnalysis(PAGE_WIGTH, PAGE_HEIGTH, COEFFICIENT, PP::Single, 0, this);
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
    } else if (qobject_cast<PageGenericWork*>(currentWidget)){
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

    PageComplete *w = new PageComplete(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, PP::Single, 0, this); //При горизонтальной ориентации меняем ширину и высоту местами
    w->setData(pc);
    w->init();
    ui->vl_printData->addWidget(w);
}


void PrintForm::on_btn_workMethodic_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintGenericData *gd = new PrintGenericData(this);
    gd->setSecondSemester(ui->rb_second->isChecked());
    gd->setWorkName("II. УЧЕБНО-МЕТОДИЧЕСКАЯ РАБОТА");
    emit getGenericTime(WorkType::MethodicWork, gd);

    for(int i = 0; i < gd->works().count(); ++i){

        auto pagePosition =PP::Middle;
        if(gd->works().count() == 1){
            pagePosition =PP::Single;
        } else if(i == 0) {
            pagePosition = PP::First;
        } else if (i == gd->works().count() - 1) {
            pagePosition = PP::Last;
        }

        PageMethodicWork *w = new PageMethodicWork(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, pagePosition, i, this); //При горизонтальной ориентации меняем ширину и высоту местами
        w->setData(gd);
        w->init();
        ui->vl_printData->addWidget(w);
    }
}


void PrintForm::on_btn_researchingWork_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintGenericData *gd = new PrintGenericData(this);
    gd->setApprovedPost("Проректор по научно-исследовательской\n"
                        "работе ФГБОУ ВО \"ВГАФК\"");
    gd->setApprovedUser("И.А. Фатьянов");
    gd->setSecondSemester(ui->rb_second->isChecked());
    gd->setWorkName("III. НАУЧНО-ИССЛЕДОВАТЕЛЬСКАЯ РАБОТА");
    emit getGenericTime(WorkType::ResearchingWork, gd);

    for(int i = 0; i < gd->works().count(); ++i){

        auto pagePosition =PP::Middle;
        if(gd->works().count() == 1){
            pagePosition =PP::Single;
        } else if(i == 0) {
            pagePosition = PP::First;
        } else if (i == gd->works().count() - 1) {
            pagePosition = PP::Last;
        }

        PageResearchingWork *w = new PageResearchingWork(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, pagePosition, i, this); //При горизонтальной ориентации меняем ширину и высоту местами
        w->setData(gd);
        w->init();
        ui->vl_printData->addWidget(w);
    }
}


void PrintForm::on_btn_sportWork_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintGenericData *gd = new PrintGenericData(this);
    gd->setApprovedPost("Проректор по молодежной политике\n"
                        "ФГБОУ ВО \"ВГАФК\"");
    gd->setApprovedUser("И.А. Кириллова");
    gd->setSecondSemester(ui->rb_second->isChecked());
    gd->setWorkName("IV. ВОСПИТАТЕЛЬНАЯ И СПОРТИВНАЯ РАБОТА");
    emit getGenericTime(WorkType::SportWork, gd);

    for(int i = 0; i < gd->works().count() || i == 0; ++i){

        auto pagePosition =PP::Middle;
        if(gd->works().count() <= 1){
            pagePosition = PP::Single;
        } else if(i == 0) {
            pagePosition = PP::First;
        } else if (i == gd->works().count() - 1) {
            pagePosition = PP::Last;
        }

        PageSportWork *w = new PageSportWork(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, pagePosition, i, this); //При горизонтальной ориентации меняем ширину и высоту местами
        w->setData(gd);
        w->init();
        ui->vl_printData->addWidget(w);
    }
}


void PrintForm::on_btn_otherWork_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintGenericData *gd = new PrintGenericData(this);
    gd->setApprovedPost(QString("Заведующий кафедрой %1\n"
                                "ФГБОУ ВО \"ВГАФК\"").arg("_____________"));
    gd->setApprovedUser("__________________");
    gd->setSecondSemester(ui->rb_second->isChecked());
    gd->setWorkName("V. ДРУГИЕ ВИДЫ РАБОТ");
    emit getGenericTime(WorkType::OtherWork, gd);

    for(int i = 0; i < gd->works().count(); ++i){

        auto pagePosition =PP::Middle;
        if(gd->works().count() == 1){
            pagePosition =PP::Single;
        } else if(i == 0) {
            pagePosition = PP::First;
        } else if (i == gd->works().count() - 1) {
            pagePosition = PP::Last;
        }

        PageOtherWork *w = new PageOtherWork(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, pagePosition, i, this); //При горизонтальной ориентации меняем ширину и высоту местами
        w->setData(gd);
        w->init();
        ui->vl_printData->addWidget(w);
    }
}


void PrintForm::on_btn_workStudy_clicked()
{
    ui->w_semester->setVisible(true);
    clearLayout(ui->vl_printData);

    PrintStudyData *ps = new PrintStudyData(this);
    ps->setSecondSemester(ui->rb_second->isChecked());
    emit getStudyTime(ps);

    for(int i = 0; i < ps->works().count(); ++i){

        auto pagePosition =PP::Middle;
        if(ps->works().count() == 1){
            pagePosition =PP::Single;
        } else if(i == 0) {
            pagePosition = PP::First;
        } else if (i == ps->works().count() - 1) {
            pagePosition = PP::Last;
        }

        PageStudy *w = new PageStudy(PAGE_HEIGTH, PAGE_WIGTH, COEFFICIENT, pagePosition, i, this); //При горизонтальной ориентации меняем ширину и высоту местами
        w->setData(ps);
        w->init();
        ui->vl_printData->addWidget(w);
    }
}

