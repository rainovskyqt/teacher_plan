#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <database/database.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sw_pages->setCurrentIndex(Pages::Login);
    ui->w_header->setVisible(false);

    Database::instance()->init("10.0.100.59", 8010);

    connect(ui->page_login, &LoginForm::enterToSystem, this, &MainWindow::enterToSystem);
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
