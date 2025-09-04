#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "database/types.h"
#include "database/database.h"
#include "updatecomments/updatecomments.h"

#include "educationwork/pageeducationwork.h"
#include "totaltime/formtotaltime.h"

#include "user/usermanager.h"

#include <teacherplan/planemanager.h>
#include "faculty/facultysettings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_plan{nullptr}
{
    ui->setupUi(this);

    checkUpdateComments();

    connect(ui->w_facultyPanel, &FacultyPanel::staffChanged, ui->w_header, &Header::setTeacher);
    connect(ui->w_header, &Header::staffChanged, this, &MainWindow::getPlans);

    connect(ui->tab_educationWork, &PageEducationWork::totalChanged, ui->tab_totalTime, &FormTotalTime::updateValues);

    init();

// connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);
// connect(ui->tab_educationWork, &FormEducationWork::clear, ui->tab_totalTime, &FormTotalTime::clearHours);

// connect(ui->tab_educationWork, &FormEducationWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
// connect(ui->tab_metod, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
// connect(ui->tab_research, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
// connect(ui->tab_sport, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);
// connect(ui->tab_other, &FormGenerikWork::planValueChanged, ui->tab_totalTime, &FormTotalTime::setPlanTime);

// connect(ui->tab_educationWork, &FormEducationWork::factValueChanged, ui->tab_educationFactical, &EducationalWorkComplite::setFactValue);

// connect(ui->tab_educationWork, &FormEducationWork::clear,
//         ui->tab_educationFactical, &EducationalWorkComplite::clearHours);

// connect(ui->tab_totalTime, &FormTotalTime::educationYearHours,
//         ui->tab_educationFactical, &EducationalWorkComplite::setYearHours);

// ui->w_header->setUser(user);
// ui->w_facultyPanel->setUser(user);


// ui->w_header->init();


#ifndef QT_DEBUG
    ui->tabWidget->setCurrentIndex(0);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveSpliterState();

    QWidget::closeEvent(e);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
}

void MainWindow::getPlans(int staffId)
{
    if(!staffId){
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        getStaffPlan(staffId);
        if(!m_plan->id()){
            ui->stackedWidget->setCurrentIndex(1);
        } else {
            ui->stackedWidget->setCurrentIndex(2);
            ui->tab_educationWork->setOwnPlan(staffId);
            ui->tab_educationWork->setPlan(m_plan->id());
            setPlanData();
#ifndef QT_DEBUG
            ui->tabWidget->setCurrentIndex(0);
#endif
        }
    }
    qApp->restoreOverrideCursor();
}

void MainWindow::getStaffPlan(int staff)
{
    if(m_plan)
        m_plan->deleteLater();

    m_plan = PlaneManager::get()->staffPlan(staff);
    if(m_plan->id())
        return;

    m_plan->setStaffId(staff);
    m_plan->setStatus(PlanStatus::Development);

}

void MainWindow::setPlanRate(double rate)
{
    if(m_plan->rate() == rate)
        return;

    m_plan->setRate(rate);
    ui->tab_totalTime->setRate(rate);
    PlaneManager::get()->savePlan(m_plan);
}

void MainWindow::init()
{
    setTypes();
    initFacultyPanel();
    loadSpliterState();
    initConnections();
    initStaffEdit();
}

void MainWindow::setTypes()
{
    ui->tab_metod->setType(WorkType::MethodicWork);
    ui->tab_research->setType(WorkType::ResearchingWork);
    ui->tab_sport->setType(WorkType::SportWork);
    ui->tab_other->setType(WorkType::OtherWork);
}

void MainWindow::loadSpliterState()
{
    auto s = Settings::get();
    QByteArray state = s.mainSplitterState();
    if (!state.isEmpty()) {
        ui->s_mainSplitter->restoreState(state);
    }
}

void MainWindow::saveSpliterState()
{
    auto s = Settings::get();
    s.setSplitterState(ui->s_mainSplitter->saveState());
}

void MainWindow::initFacultyPanel()
{
    ui->w_facultyPanel->init();
    if(ui->w_facultyPanel->canBeVisible()){
        ui->a_showFacultyPanel->setEnabled(true);
        ui->w_facultyPanel->setVisible(Settings::get().facultyPanel());
        ui->a_showFacultyPanel->setChecked(Settings::get().facultyPanel());

        connect(ui->a_showFacultyPanel, &QAction::triggered, this, [&](bool checked){
            ui->w_facultyPanel->setVisible(checked);
            auto s = Settings::get();
            s.setFacultyPanel(checked);
        });
    } else {
        ui->a_showFacultyPanel->setEnabled(false);
        ui->w_facultyPanel->setVisible(false);
    }
}

void MainWindow::initConnections()
{
    connect(ui->a_exit, &QAction::triggered, this, []{ qApp->exit(0); });
}

void MainWindow::initStaffEdit()
{
    using R = UserRights;
    auto u = UserManager::get()->user();
    if(u->hasAnyRights({R::DepartmentStaffEdit, R::TotalAdmin}))
        ui->a_depStaffEdit->setEnabled(true);
    else
        ui->a_depStaffEdit->setEnabled(false);
}

void MainWindow::checkUpdateComments()
{
    UpdateComments comments;
    if(comments.loadComments(UserManager::get()->user()->id()))
        comments.exec();
    if(comments.dontShow())
        comments.setViewed(UserManager::get()->user()->id());
}

void MainWindow::setPlanData()
{
    auto tab =  ui->tab_totalTime;
    tab->setRate(m_plan->rate());
    connect(tab, &FormTotalTime::rateChanged, this, &MainWindow::setPlanRate);
}

void MainWindow::on_btn_create_clicked()
{
    PlaneManager::get()->savePlan(m_plan);
    getPlans(m_plan->staffId());
}


void MainWindow::on_a_depStaffEdit_triggered()
{
    FacultySettings *s = new FacultySettings(this);
    s->exec();
    s->deleteLater();
}

