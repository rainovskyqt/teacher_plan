#include "facultysettings.h"
#include "ui_facultysettings.h"

#include <QDebug>
#include <QListWidgetItem>

#include <user/usermanager.h>
#include <database/dictionary/dictionarymanager.h>
#include "faculty/departmentlistview.h"

FacultySettings::FacultySettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FacultySettings)
    , m_staff(nullptr)
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
    loadDepartments();
    initStaffModel();
    selectOwnDepartment();

    connect(ui->cb_year, &YearCombobox::yearChanged, this, &FacultySettings::changeYear);
}

void FacultySettings::setBossVisible()
{
    bool admin = UserManager::get()->user()->hasAnyRights({UserRights::TotalAdmin});
    ui->w_depBoss->setVisible(admin);
    ui->lv_faculties->setVisible(admin);
}

void FacultySettings::loadDepartments()
{
    ui->lv_faculties->setModel(DictionaryManager::get()->departments());
    ui->lv_faculties->setModelColumn(DictionaryModel::Name);
}

void FacultySettings::selectOwnDepartment()
{
    int depId = UserManager::get()->user()->mainStaff()->departmentId();
    selectDepartmentSettings(depId);
    ui->lv_faculties->selectDepartment(depId);
}

void FacultySettings::selectDepartmentSettings(int depId, int yearId)
{
    ui->stackedWidget->setCurrentIndex(1);
    auto year = yearId;
    if(!year)
        year = DictionaryManager::get()->years()->currentYearId();

    m_staff->departmentList(year, depId);
    ui->lv_staffList->setModel(m_staff);
    ui->lv_staffList->setModelColumn(1);
}

void FacultySettings::initStaffModel()
{
    if(m_staff == nullptr)
        m_staff = new ModelStaffList(this);
}

void FacultySettings::on_lv_faculties_clicked(const QModelIndex &index)
{
    auto model = ui->lv_faculties->model();
    auto depId = model->data(model->index(index.row(), DictionaryModel::Id)).toInt();

    auto yearId = ui->cb_year->selectedYear();
    selectDepartmentSettings(depId, yearId);
}

void FacultySettings::changeYear(int yearId)
{
    auto model = ui->lv_faculties->model();
    auto indexList = ui->lv_faculties->selectionModel()->selectedIndexes();
    if(indexList.count() == 0)
        return;

    auto depId = model->data(model->index(indexList.at(0).row(), DictionaryModel::Id)).toInt();

    selectDepartmentSettings(depId, yearId);
}

