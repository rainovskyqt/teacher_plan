#include "header.h"
#include "ui_header.h"

#include <QListView>
#include <QMessageBox>
#include <QDebug>

#include "user/usermanager.h"
#include "database/dictionary/dictionarymanager.h"
#include "misc/months.h"
#include "teacherplan/planemanager.h"

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);
    this->setVisible(false);

    connect(ui->cb_years, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](){
        auto years = DictionaryManager::get()->years();;
        int yearId = years->data(years->index(ui->cb_years->currentIndex(), DictionaryModel::Id)).toInt();
        Months::get()->loadSettings(yearId);
        setDepartments(yearId);
    });

    connect(ui->cb_post, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Header::changePost);
    connect(ui->cb_department, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Header::setPosts);
}

Header::~Header()
{
    delete ui;
}

void Header::init()
{
    this->setVisible(true);

    setDepartments(0);
    setTeacherData();

    ui->lbl_planNumbers->setVisible(false);
    ui->lbl_planNumbersText->setVisible(false);
    ui->sw_approved->setVisible(false);
    ui->w_protocol->setVisible(false);
}

void Header::setTeacher(int id)
{
    if(!id)
        emit staffChanged(0);

    m_modelStaff.loadByUserId(id);
    init();
}

void Header::setDepartments(int index)
{
    ui->cb_department->clear();
    auto years = DictionaryManager::get()->years();
    int id = years->data(years->index(index, DictionaryModel::Id)).toInt();
    auto deps = m_modelStaff.departments(id);
    for(const auto &d : qAsConst(deps))
        ui->cb_department->addItem(d.second, d.first);
}

void Header::setPosts(int index)
{
    Q_UNUSED(index)
    ui->cb_post->clear();
    int id = ui->cb_department->currentData().toInt();
    auto posts = m_modelStaff.posts(id);
    for(const auto &p : qAsConst(posts))
        ui->cb_post->addItem(p.second, p.first);
}

void Header::changePost(int index)
{
    if( index == -1 )
        return;
    int id = ui->cb_post->currentData().toInt();
    emit staffChanged(id);
}

void Header::setTeacherData()
{
    ui->line_fio->setText(QString("%1 %2 %3").arg(m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserSurname)).toString(),
                                                  m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserName)).toString(),
                                                  m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserMiddleName)).toString()));
}


// void Header::on_btn_approvedCancel_clicked()
// {
//     ui->sw_approved->setCurrentIndex(Development);
//     m_currentPlan->setStatusId(TeacherPlan::Development);
//     Database::get()->updateTeacherPlan(m_currentPlan);
// }


// void Header::on_btn_toApprove_clicked()
// {
//     ui->sw_approved->setCurrentIndex(OnApproved);
//     m_currentPlan->setStatusId(TeacherPlan::OnApproved);
//     Database::get()->updateTeacherPlan(m_currentPlan);
// }

// void Header::setStatus(int status)
// {
//     int page = 0;
//     switch (status) {
//     case TeacherPlan::Development:
//         page = Development;
//         break;
//     case TeacherPlan::OnApproved:
//         page = OnApproved;
//         break;
//     case TeacherPlan::Approveded:
//         page = Approveded;
//         break;
//     }
//     ui->sw_approved->setCurrentIndex(page);
// }

// void Header::setProtocol(TeacherPlan *plan)
// {
//     auto date = plan->protocolDate();
//     if(date.isValid()){
//         ui->w_protocol->setVisible(true);
//         ui->lbl_protolDate->setText(date.toString("dd.MM.yyyy"));
//         ui->lbl_protolNumber->setText(plan->protocolNumber());
//     } else {
//         ui->w_protocol->setVisible(false);
//     }
// }

// void Header::setApproved(TeacherPlan *plan)
// {
//     auto date = plan->approveDate();
//     // auto user = plan->approveUserId();

//     if(date.isValid()){
//         ui->lbl_approvedDate->setText(date.toString("dd.MM.yyyy"));
//         //     if(user)
//         //         ui->lbl_approvedName->setText(QString("%1 %2 %3.%4.")
//         //                                           .arg(user->userData()->rang(),
//         //                                                user->userData()->surname(),
//         //                                                !user->userData()->name().isEmpty() ? user->userData()->name().at(0) : QString(),
//         //                                                !user->userData()->middle_name().isEmpty() ? user->userData()->middle_name().at(0) : QString())
//         //                                       );
//     }
// }

//bool Header::saveQustion()
//{
//    if(!m_currentPlan || !m_currentPlan->isChanged())
//        return true;

//    int answer = QMessageBox::question(this, "Сохрание индивидуального плана", "Индивидуальный план был изменен, сохранить изменения?",
//                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
//    if(answer == QMessageBox::Cancel){
//        return false;
//    } else if(answer == QMessageBox::Yes) {
//        savePlan();
//    }
//    m_currentPlan->setChanged(false);
//    return true;
//}
