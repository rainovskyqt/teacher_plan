#include "facultypanel.h"
#include "ui_facultypanel.h"

#include "database/database.h"

#include "user/usermanager.h"
#include "user/user.h"

// using R = UserRights;

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
    ui->lbl_fio->setText(user->nameShort());
    if(auto mainStaff = user->mainStaff()){
        ui->lbl_department->setText(mainStaff->departmentName());
        ui->lbl_post->setText(mainStaff->postName());
    }
}

// bool FacultyPanel::personalPlanOnly()
// {
//     bool boss = m_user->hasAnyRights({R::DepartmentTeacherPlans,
//                                       R::AllTeacherPlans});

//     return !boss;
// }


// void FacultyPanel::loadStaff()
// {
//     ui->tree_plans->clear();
//     int dep = m_user->hasAnyRights({R::DepartmentTeacherPlans}) ? m_departmentId : 0;
//     auto staffList = Database::get()->staffList(dep);

//     auto departments = staffList.uniqueKeys();
//     std::sort(departments.begin(), departments.end());

//     for(const QString& key : departments) {
//         QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->tree_plans);
//         parentItem->setText(0, key);

//         auto staff = staffList.values(key);
//         auto staffUnique = QSet<QPair<QString, int>>(staff.begin(), staff.end());

//         for(const auto value : staffUnique) {
//             QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
//             childItem->setData(0, Qt::UserRole, value.second);
//             childItem->setText(0, value.first);
//         }
//     }
// }

// void FacultyPanel::on_tree_plans_itemClicked(QTreeWidgetItem *item, int column)
// {
//     auto id = item->data(0, Qt::UserRole).toInt();
//     if(id)
//         staffChanget(id);
// }

