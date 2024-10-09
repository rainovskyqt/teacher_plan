#include "mainwindow.h"
#include "settings.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "database/types.h"
#include "database/database.h"
#include "updatecomments/updatecomments.h"

#include "educationwork/pageeducationwork.h"

#include "user/usermanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    checkUpdateComments();

    connect(ui->w_facultyPanel, &FacultyPanel::staffChanged, ui->w_header, &Header::setTeacher);
    connect(ui->w_header, &Header::staffChanged, ui->tab_educationWork, &PageEducationWork::setStaff);

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

void MainWindow::init()
{
    setTypes();
    initFacultyPanel();
    loadSpliterState();
    initConnections();
}

// void MainWindow::setPlanData(TeacherPlan *plan)
// {
//     m_currentPlan = plan;
//     if(!plan->baseId()){
//         ui->stackedWidget->setCurrentIndex(0);
//         ui->label->setText(tr("Индивидуальный план не создан"));
//     } else {
//         ui->stackedWidget->setCurrentIndex(1);
//         ui->tab_totalTime->setPlanData(plan);
//         ui->tab_educationWork->setPlanData(plan);
//         ui->tab_metod->setPlanData(plan);
//         ui->tab_research->setPlanData(plan);
//         ui->tab_sport->setPlanData(plan);
//         ui->tab_other->setPlanData(plan);
//         ui->stackedWidget->setCurrentIndex(TotalTime);
//     }
// }

void MainWindow::setTypes()
{
    // ui->tab_metod->setType(WorkType::MethodicWork);
    // ui->tab_research->setType(WorkType::ResearchingWork);
    // ui->tab_sport->setType(WorkType::SportWork);
    // ui->tab_other->setType(WorkType::OtherWork);
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

void MainWindow::checkUpdateComments()
{
    UpdateComments comments;
    if(comments.loadComments(UserManager::get()->user()->id()))
        comments.exec();
    if(comments.dontShow())
        comments.setViewed(UserManager::get()->user()->id());
}

// void MainWindow::on_btn_create_clicked()
// {
//     m_currentPlan->setBaseId(Database::get()->updateTeacherPlan(m_currentPlan));
//     ui->w_header->setPlan();
// }

