#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database/database.h"
#include "login/user.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sw_pages->setCurrentIndex(Pages::Login);

    Database::get()->init("10.0.100.157", 8020);
    // Database::get()->init("10.0.2.18", 8020);

    connect(ui->page_login, &LoginForm::enterToSystem,
            this, [&](int id){
                User::get()->setBaseId(id);
                ui->sw_pages->setCurrentIndex(Pages::TotalTime);
                ui->w_header->init();
            });

    connect(ui->w_header, &Header::currentPlanChanged, this, [&](TeacherPlan *plan){
        ui->tab_totalTime->setPlaneData(plan);
    });
    connect(ui->tab_totalTime, &FormTotalTime::modelDataChanged, ui->w_header, &Header::modelDataChanged);
    connect(ui->tab_totalTime, &FormTotalTime::savePlan, ui->w_header, &Header::savePlan);
    connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enterToSystem()
{
    ui->w_header->setVisible(true);
    ui->sw_pages->setCurrentIndex(Pages::TotalTime);
}
