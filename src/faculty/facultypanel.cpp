#include "facultypanel.h"
#include "ui_facultypanel.h"

#include <QComboBox>
#include <QDebug>

#include "database/dictionary/dictionarymanager.h"
#include "user/usermanager.h"
#include "user/user.h"

using R = UserRights;

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

void FacultyPanel::init()
{
    auto user = UserManager::get()->user();

    setUserData(user);

    if(!personalPlanOnly()){
        setYearModel();
        setModel();
        loadTechers(ui->cb_year->currentIndex());
        connect(ui->cb_year, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FacultyPanel::loadTechers);
        setOwnPlans();
    }
}

bool FacultyPanel::canBeVisible()
{
    return !personalPlanOnly();
}

bool FacultyPanel::personalPlanOnly()
{
    auto user = UserManager::get()->user();
    bool boss = user->hasAnyRights({R::DepartmentTeacherPlans,
                                    R::AllTeacherPlans});

    return !boss;
}

void FacultyPanel::setYearModel()
{
    m_modelYear.setSourceModel(DictionaryManager::get()->years());
    ui->cb_year->setModel(&m_modelYear);
    ui->cb_year->setModelColumn(DictionaryModel::Name);

}

void FacultyPanel::setUserData(User *user)
{
    ui->lbl_fio->setText(user->nameShort());
    if(auto mainStaff = user->mainStaff()){
        ui->lbl_department->setText(mainStaff->departmentName());
        ui->lbl_post->setText(mainStaff->postName());
    }
}

void FacultyPanel::setModel()
{
    m_model.setSourceModel(new ModelStaffList(this));
    ui->tree_plans->setModel(&m_model);

    connect(ui->btn_own, &QPushButton::clicked, this, &FacultyPanel::setOwnPlans);

    connect(ui->tree_plans->selectionModel() , &QItemSelectionModel::currentChanged,
            this, [&](const QModelIndex &current, const QModelIndex &previous){
                Q_UNUSED(previous)
                int id = 0;
                if(m_model.itemFromIndex(current)->data(Qt::UserRole + 1).toBool())
                    id = m_model.itemFromIndex(current)->data(Qt::UserRole).toInt();
                emit staffChanged(id);
            });

}

void FacultyPanel::setOwnPlans()
{
    auto model = qobject_cast<ModelFaculty*>(ui->tree_plans->model());
    int ownId = UserManager::get()->user()->id();
    int depId = UserManager::get()->user()->mainStaff()->departmentId();
    ui->tree_plans->setCurrentIndex(model->getUserIndex(ownId, depId));
}

void FacultyPanel::loadTechers(int index)
{
    auto user = UserManager::get()->user();
    int dep = user->hasAnyRights({R::DepartmentTeacherPlans}) ? user->mainStaff()->departmentId() : 0;
    int year = m_modelYear.data(m_modelYear.index(index, 0)).toInt();

    m_model.loadByDepartment(year, dep);
}
