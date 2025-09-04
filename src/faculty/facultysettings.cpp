#include "facultysettings.h"
#include "ui_facultysettings.h"

#include <user/usermanager.h>

#include <database/dictionary/dictionarymanager.h>

FacultySettings::FacultySettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FacultySettings)
{
    ui->setupUi(this);

    init();
}

FacultySettings::~FacultySettings()
{
    delete ui;
}

void FacultySettings::init()
{
    setBossVisible();
}

void FacultySettings::setBossVisible()
{
    bool admin = UserManager::get()->user()->hasAnyRights({UserRights::TotalAdmin});
    ui->w_depBoss->setVisible(admin);
    ui->lw_faculties->setVisible(admin);
}

void FacultySettings::loadDepartments()
{
    // ui->l DictionaryManager::get()->departments();
}
