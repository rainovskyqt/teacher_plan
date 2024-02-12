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

    Database::get()->init("10.0.100.59", 8010);

    connect(ui->page_login, &LoginForm::enterToSystem,
            this, [&](int id, QString token, QString refreshToken){
        User::get()->setData(id, token, refreshToken);
        ui->sw_pages->setCurrentIndex(Pages::TotalTime);
        ui->w_header->init();
    });
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
