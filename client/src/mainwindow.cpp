#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database/database.h"
#include "login/user.h"

#include <QMessageBox>

MainWindow::MainWindow(User *user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_userBaseId{0}
    ,m_currentPlanId{0}
{
    ui->setupUi(this);

    connect(ui->w_header, &Header::currentPlanChanged, ui->tab_totalTime, &FormTotalTime::setPlanData);
    connect(ui->w_header, &Header::currentPlanChanged, ui->tab_educationWork, &FormEducationWork::setPlanData);
    connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);

    connect(ui->tab_educationWork, &FormEducationWork::firstPlaneChanget, ui->tab_totalTime, &FormTotalTime::setFirstSemester);
    connect(ui->tab_educationWork, &FormEducationWork::secondPlaneChanget, ui->tab_totalTime, &FormTotalTime::setSecondSemester);


    ui->w_header->setUser(user);
    ui->w_header->init();

    setTypes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTypes()
{
    ui->tab_metod->setType(WorkType::MethodicWork);
    ui->tab_research->setType(WorkType::ResearchingWork);
    ui->tab_sport->setType(WorkType::SportWork);
    ui->tab_other->setType(WorkType::OtherWork);
}
