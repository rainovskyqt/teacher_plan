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

void FacultyPanel::setUser(User *newUser)
{
    m_user = newUser;

    ui->lbl_fio->setText(QString("%1 %2. %3.").arg(m_user->userData()->surname(),
                                                   m_user->userData()->name().at(0),
                                                   m_user->userData()->middle_name().at(0)));
    setFaculty();
    setVisibility();
}

void FacultyPanel::setVisibility()
{
    using R = UserRights;
    bool visible = m_user->hasAnyRights({R::DepartmentTeacherPlans,
                                         R::AllTeacherPlans});
    this->setVisible(visible);
}

void FacultyPanel::setFaculty()
{
    auto posts = m_user->posts();
    foreach(auto p, posts){
        if(p.main){
            ui->lbl_department->setText(p.depName);
            ui->lbl_post->setText(p.postName);
        }
    }
}
