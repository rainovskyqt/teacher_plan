#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <database/database.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sw_pages->setCurrentIndex(Pages::Login);

    Database::instance()->init();        // TODO setup

    connect(ui->page_login, &LoginForm::enterToSystem, this, [&](int id){
        m_userBaseId = id;
        ui->sw_pages->setCurrentIndex(Pages::TotalTime);
        ui->w_header->init(m_userBaseId);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
