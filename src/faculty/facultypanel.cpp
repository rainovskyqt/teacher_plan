#include "facultypanel.h"
#include "ui_facultypanel.h"

#include <QDebug>

#include "database/database.h"
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
        setModel(user);
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

void FacultyPanel::setUserData(User *user)
{
    ui->lbl_fio->setText(user->nameShort());
    if(auto mainStaff = user->mainStaff()){
        ui->lbl_department->setText(mainStaff->departmentName());
        ui->lbl_post->setText(mainStaff->postName());
    }
}

void FacultyPanel::setModel(User *user)
{
    ui->tree_plans->setModel(&model);
    int dep = user->hasAnyRights({R::DepartmentTeacherPlans}) ? user->mainStaff()->departmentId() : 0;
    model.loadStaff(dep);

    connect(ui->btn_own, &QPushButton::clicked, this, &FacultyPanel::setOwnPlans);

    connect(ui->tree_plans->selectionModel() , &QItemSelectionModel::currentChanged,
            this, [&](const QModelIndex &current, const QModelIndex &previous){
                Q_UNUSED(previous)
                int id = model.itemFromIndex(current)->data(Qt::UserRole).toInt();
                emit staffChanged(id);
            });

}

void FacultyPanel::setOwnPlans()
{
    auto model = qobject_cast<ModelStaffList*>(ui->tree_plans->model());
    int ownId = UserManager::get()->user()->id();
    int depId = UserManager::get()->user()->mainStaff()->departmentId();
    ui->tree_plans->setCurrentIndex(model->getUserIndex(ownId, depId));
}
