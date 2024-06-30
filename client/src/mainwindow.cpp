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
//    connect(ui->tab_totalTime, &FormTotalTime::modelDataChanged, ui->w_header, &Header::modelDataChanged);
//    connect(ui->tab_totalTime, &FormTotalTime::savePlan, ui->w_header, &Header::savePlan);
    connect(ui->tab_totalTime, &FormTotalTime::rateChanged, ui->w_header, &Header::setRate);

    ui->w_header->setUser(user);
    ui->w_header->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
