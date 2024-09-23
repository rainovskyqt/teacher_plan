#include "facultypanel.h"
#include "ui_facultypanel.h"

#include "database/database.h"

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
    int dep = m_user->hasAnyRights({R::DepartmentTeacherPlans}) ? m_departmentId : 0;
    auto list = Database::get()->staffList(dep);

    ui->tree_plans->clear();

    foreach(const QString& key, list.uniqueKeys()) {
        QTreeWidgetItem* parentItem = new QTreeWidgetItem(ui->tree_plans);
        parentItem->setText(0, key);

        foreach(const auto value, list.values(key)) {
            QTreeWidgetItem* childItem = new QTreeWidgetItem(parentItem);
            childItem->setData(0, Qt::UserRole, value.first);
            childItem->setText(0, value.second);
        }
    }
}
