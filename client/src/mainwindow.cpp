#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database/database.h"
#include "login/user.h"

#include <QMessageBox>

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    setTypes();

    connect(ui->w_header, &Header::currentPlanChanged, this, &MainWindow::setPlanData);
    connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);

    connect(ui->tab_educationWork, &FormEducationWork::clear, ui->tab_totalTime, &FormTotalTime::clearHours);
    connect(ui->tab_educationWork, &FormEducationWork::firstPlaneChanged, ui->tab_totalTime, &FormTotalTime::setFirstSemester);
    connect(ui->tab_educationWork, &FormEducationWork::secondPlaneChanged, ui->tab_totalTime, &FormTotalTime::setSecondSemester);

    connect(ui->tab_educationWork, &FormEducationWork::factValueChanged, ui->tab_educationFactical, &EducationalWorkComplite::setFactValue);

    connect(ui->tab_educationWork, &FormEducationWork::clear,
            ui->tab_educationFactical, &EducationalWorkComplite::clearHours);

    connect(ui->tab_totalTime, &FormTotalTime::educationYearHours,
            ui->tab_educationFactical, &EducationalWorkComplite::setYearHours);

    ui->w_header->setUser(user);
    ui->w_header->init();


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
        ui->label->setText(tr("Индивидуальный план не создан"));
    } else {
        ui->tab_totalTime->setPlanData(plan);
        ui->tab_educationWork->setPlanData(plan);
        ui->tab_metod->setPlanData(plan);
        ui->tab_research->setPlanData(plan);
        ui->tab_sport->setPlanData(plan);
        ui->tab_other->setPlanData(plan);
        ui->stackedWidget->setCurrentIndex(TotalTime);
    }
}

void MainWindow::setTypes()
{
    ui->tab_metod->setType(WorkType::MethodicWork);
    ui->tab_research->setType(WorkType::ResearchingWork);
    ui->tab_sport->setType(WorkType::SportWork);
    ui->tab_other->setType(WorkType::OtherWork);
}

void MainWindow::on_btn_create_clicked()
{
    m_currentPlan->setBaseId(Database::get()->updateTeacherPlan(m_currentPlan));
    ui->w_header->setPlan();
}

