#include "facultypanel.h"
#include "ui_facultypanel.h"

FacultyPanel::FacultyPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FacultyPanel)
{
    ui->setupUi(this);
}

FacultyPanel::~FacultyPanel()
{
    delete ui;
}
