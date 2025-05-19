#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database/database.h"
#include "login/user.h"

#include <QMessageBox>

#include <updatecomments/updatecomments.h>

#include <print/printform.h>

#include <print/datafiles/printtotaldata.h>
#include <print/datafiles/printstudydata.h>

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setTypes();

    connect(ui->w_header, &Header::currentPlanChanged, this, &MainWindow::setPlanData);
    connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);
    connect(ui->tab_educationWork, &FormEducationWork::clear, ui->tab_totalTime, &FormTotalTime::clearHours);

    connect(ui->tab_educationWork, &FormEducationWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
    connect(ui->tab_metod, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
    connect(ui->tab_research, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
    connect(ui->tab_sport, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
    connect(ui->tab_other, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);

    connect(ui->tab_educationWork, &FormEducationWork::monthValueChanged, ui->tab_educationFactical, &EducationalWorkComplite::setMonthValue);

    connect(ui->tab_educationWork, &FormEducationWork::clear,
            ui->tab_educationFactical, &EducationalWorkComplite::clearHours);

    connect(ui->tab_totalTime, &FormTotalTime::educationYearHours,
            ui->tab_educationFactical, &EducationalWorkComplite::setYearHours);

    ui->w_header->setUser(user);
    ui->w_facultyPanel->setUser(user);

    connect(ui->w_facultyPanel, &FacultyPanel::staffChanget, this, [&](int userId){
        ui->w_header->setUser(userId);
        ui->w_header->init();
    });

    ui->w_header->init();

    checkUpdateComments(user->baseId());

#ifndef QT_DEBUG
    ui->tabWidget->setCurrentIndex(0);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPlanData(TeacherPlan *plan)
{
    m_currentPlan = plan;
    if(!plan->baseId()){
        ui->stackedWidget->setCurrentIndex(0);
        ui->label->setText(tr("Индивидуальный план не создан"));
    } else {
        ui->stackedWidget->setCurrentIndex(1);
        ui->tab_totalTime->setPlanData(plan);
        ui->tab_educationWork->setPlanData(plan);
        ui->tab_metod->setPlanData(plan);
        ui->tab_research->setPlanData(plan);
        ui->tab_sport->setPlanData(plan);
        ui->tab_other->setPlanData(plan);
        ui->stackedWidget->setCurrentIndex(TotalTime);
        ui->tab_educationFactical->setPlanId(plan->baseId());
    }
}

void MainWindow::setTypes()
{
    ui->tab_metod->setType(WorkType::MethodicWork);
    ui->tab_research->setType(WorkType::ResearchingWork);
    ui->tab_sport->setType(WorkType::SportWork);
    ui->tab_other->setType(WorkType::OtherWork);
}

void MainWindow::checkUpdateComments(int userId)
{
    UpdateComments comments;
    if(comments.loadComments(userId))
        comments.exec();
    if(comments.dontShow())
        comments.setViewed();
}

void MainWindow::on_btn_create_clicked()
{
    m_currentPlan->setBaseId(Database::get()->updateTeacherPlan(m_currentPlan));
    ui->w_header->setPlan();
}

void MainWindow::on_a_exit_triggered()
{
    qApp->exit();
}


void MainWindow::on_action_print_triggered()
{
    PrintForm *pf = new PrintForm(m_currentPlan, ui->w_header->user(), this);

    connect(pf, &PrintForm::getTotalTime, this, &MainWindow::setTotalTime);
    connect(pf, &PrintForm::getCompliteTime, this, &MainWindow::setCompliteTime);
    connect(pf, &PrintForm::getGenericTime, this, &MainWindow::setGenericTime);
    connect(pf, &PrintForm::getStudyTime, this, &MainWindow::setStudyTime);

    pf->exec();
}

void MainWindow::setTotalTime(PrintTotalData *total)
{
    using W = WorkType;
    using S = PlanTime::Semester;

    auto w = ui->tab_totalTime;

    for(int type = (int)W::Educational; type <= (int)W::OtherWork; ++type){
        auto t = static_cast<W>(type);
        total->setTime(t, S::FirstSemester, w->getTime(t, S::FirstSemester));
        total->setTime(t, S::SecondSemestr, w->getTime(t, S::SecondSemestr));
    }
}

void MainWindow::setCompliteTime(PrintComplite *c)
{
    ui->tab_educationFactical->setCompliteTime(c);
}

void MainWindow::setGenericTime(WorkType type, PrintGenericData *c)
{
    if(type == WorkType::MethodicWork)
        ui->tab_metod->setGenericTime(c);
    else if(type == WorkType::ResearchingWork)
        ui->tab_research->setGenericTime(c);
    else if(type == WorkType::SportWork)
        ui->tab_sport->setGenericTime(c);
    else if(type == WorkType::OtherWork)
        ui->tab_other->setGenericTime(c);
}

void MainWindow::setStudyTime(PrintStudyData *c)
{
    ui->tab_educationWork->setStudyTime(c);
}
