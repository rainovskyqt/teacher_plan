#include "facultysettings.h"
#include "ui_facultysettings.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QMessageBox>

#include <user/usermanager.h>
#include <database/dictionary/dictionarymanager.h>
#include "faculty/departmentlistview.h"

#include <staff/staffmanager.h>
#include <staff/staffsettings.h>

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

void FacultySettings::reloadList()
{
    auto model = ui->lv_faculties->model();
    auto rows = ui->lv_faculties->selectionModel()->selectedIndexes();
    if(rows.isEmpty())
        return;

    auto depId = model->data(model->index(rows.at(0).row(), DictionaryModel::Id)).toInt();

    auto yearId = ui->cb_year->selectedYear();
    selectDepartmentSettings(depId, yearId);
}

void FacultySettings::setBossVisible()
{
    bool admin = UserManager::get()->user()->isAdmin();
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
    ui->lv_staffList->setModelColumn(ModelStaffList::DepUserFullname);
}

void FacultySettings::initStaffModel()
{
    if(m_staff == nullptr)
        m_staff = new ModelStaffList(this);
}

int FacultySettings::getStaffId()
{
    auto model = ui->lv_staffList->model();
    auto indexList = ui->lv_staffList->selectionModel()->selectedIndexes();
    if(indexList.count() == 0){
        QMessageBox::information(this, "Не выбран сотрудник", "Выберите сотрудника из списка");
        return 0;
    }

    auto staffId = model->data(model->index(indexList.at(0).row(), ModelStaffList::DepStaffId)).toInt();
    return staffId;
}

void FacultySettings::on_lv_faculties_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    reloadList();
}

void FacultySettings::changeYear(int yearId)
{
    Q_UNUSED(yearId)
    reloadList();
}

void FacultySettings::on_btn_add_clicked()
{
    StaffSettings *s = new StaffSettings(0, this);
    s->exec();
    s->deleteLater();
    reloadList();
}

void FacultySettings::on_btn_edit_clicked()
{
    int id = getStaffId();
    if(!id)
        return;

    StaffSettings *s = new StaffSettings(id, this);
    s->exec();
    s->deleteLater();
    reloadList();
}

void FacultySettings::on_btn_delete_clicked()
{
    int id = getStaffId();
    if(!id)
        return;

    if(QMessageBox::information(this, "Удаление ставки", "Удалить ставку?") ==
        QMessageBox::Cancel)
        return;

    StaffManager::get()->deleteStaff(id);
    reloadList();
}

