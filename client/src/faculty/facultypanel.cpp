#include "facultypanel.h"
#include "ui_facultypanel.h"

#include "database/database.h"
#include <QSet>

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

void FacultyPanel::setUser(User *newUser)
{
    m_user = newUser;

    if(personalPlanOnly()){
        this->setVisible(false);
        return;
    }

    ui->lbl_fio->setText(QString("%1 %2. %3.").arg(m_user->userData()->surname(),
                                                   m_user->userData()->name().at(0),
                                                   m_user->userData()->middle_name().at(0)));
    setFaculty();
    loadStaff();
}

bool FacultyPanel::personalPlanOnly()
{
    bool boss = m_user->hasAnyRights({R::DepartmentTeacherPlans,
                                      R::AllTeacherPlans});

    return !boss;
}

void FacultyPanel::setFaculty()
{
    auto posts = m_user->posts();
    foreach(auto p, posts){
        if(p.main){
            m_departmentId = p.departmentId;
            ui->lbl_department->setText(p.depName);
            ui->lbl_post->setText(p.postName);
        }
    }
}

void FacultyPanel::loadStaff()
{
    ui->tree_plans->clear();
    int dep = m_user->hasAnyRights({R::DepartmentTeacherPlans}) ? m_departmentId : 0;
    auto staffList = Database::get()->staffList(dep);

    auto departments = staffList.uniqueKeys();
    std::sort(departments.begin(), departments.end());

    for(const QString& key : departments) {
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->tree_plans);
        parentItem->setText(0, key);

        auto staff = staffList.values(key);
        // auto staffUnique = QSet<QPair<QString, int>>(staff.begin(), staff.end());
        QSet<QPair<QString, int>> staffUnique = QSet<QPair<QString, int>>::fromList(staff);

        for(const auto value : qAsConst(staffUnique)) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setData(0, Qt::UserRole, value.second);
            childItem->setText(0, value.first);
        }
    }
}

void FacultyPanel::on_tree_plans_itemClicked(QTreeWidgetItem *item, int column)
{
    auto id = item->data(0, Qt::UserRole).toInt();
    if(id)
        emit staffChanget(id);
}

