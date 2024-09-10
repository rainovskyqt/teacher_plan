#include "header.h"
#include "ui_header.h"

#include <QListView>
#include <QMessageBox>


#include "login/user.h"

#include <database/adapters/dictionaryadapter.h>

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
    ,m_currentPlan{nullptr}
{
    ui->setupUi(this);
    this->setVisible(false);
    ui->lbl_planNumbers->setVisible(false);
    ui->lbl_planNumbersText->setVisible(false);

    setCurrentIndexes();
}

Header::~Header()
{
    delete ui;
}

void Header::init()
{
    this->setVisible(true);

    loadData();
    setStaffData();
}

User *Header::user() const
{
    return m_user;
}

void Header::setUser(User *newUser)
{
    m_user = newUser;
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

void Header::setStaffData()
{
    auto d = m_user->userData();
    ui->line_fio->setText(QString("%1 %2 %3 %4")
                              .arg(d->rang(),
                                   d->surname(),
                                   d->name(),
                                   d->middle_name()));
    setUserDepartments();
}

void Header::loadData()
{
    DictionaryAdapter::setYears(ui->cb_years);
    DictionaryAdapter::setDictionary(m_departments, Database::Department);
    DictionaryAdapter::setDictionary(m_posts, Database::Post);
}

void Header::setDefaultData(int userId, int yearId, int departmentId, int postId)
{
    m_currentPlan = new TeacherPlan(this);
    setStatus(TeacherPlan::Development);
    m_currentPlan->setStatusId(TeacherPlan::Development);
    m_currentPlan->setUserId(userId);
    m_currentPlan->setYearId(yearId);
    m_currentPlan->setDepartmentId(departmentId);
    m_currentPlan->setPostId(postId);
    ui->w_protocol->setVisible(false);

    emit currentPlanChanged(m_currentPlan);
}

void Header::setCurrentIndexes()
{
    m_currentIndex.insert(ui->cb_years, -1);
    m_currentIndex.insert(ui->cb_department, -1);
    m_currentIndex.insert(ui->cb_post, -1);
}

bool Header::changeIndex(QComboBox *box)
{
    if(box->currentIndex() == m_currentIndex.value(box))
        return false;

//    if(!saveQustion()){
//        box->setCurrentIndex(m_currentIndex.value(box));
//        return false;
//    }

    m_currentIndex.insert(box, box->currentIndex());

    return true;
}


void Header::setUserDepartments()
{
    ui->cb_department->clear();

    auto userDep = m_user->posts().keys();

    foreach (auto dep, m_departments) {
        if(userDep.contains(dep.id()))
            ui->cb_department->addItem(dep.name(), dep.id());
    }
}

void Header::setPlan()
{
    auto year = ui->cb_years->currentData().toInt();
    auto dep = ui->cb_department->currentData().toInt();
    auto post = ui->cb_post->currentData().toInt();

    setPlanData(Database::get()->requestPlan(m_user->baseId(), year, dep, post));
}

QString Header::currentTecher()
{
    return ui->line_fio->text();
}

QString Header::currentDepartment()
{
    return ui->cb_department->currentText();
}

QString Header::currentYear()
{
    return ui->cb_years->currentText();
}

void Header::setPlanData(TeacherPlan *plan)
{
    m_currentPlan = plan;
    setStatus(m_currentPlan->statusId());
    setProtocol(m_currentPlan);
    setApproved(m_currentPlan);
    qDebug() << "Загружен план с id: " << plan->baseId();

    emit currentPlanChanged(m_currentPlan);
}

void Header::setStatus(int status)
{
    int page = 0;
    switch (status) {
    case TeacherPlan::Development:
        page = Development;
        break;
    case TeacherPlan::OnApproved:
        page = OnApproved;
        break;
    case TeacherPlan::Approveded:
        page = Approveded;
        break;
    }
    ui->sw_approved->setCurrentIndex(page);
}

void Header::setProtocol(TeacherPlan *plan)
{
    auto date = plan->protocolDate();
    if(date.isValid()){
        ui->w_protocol->setVisible(true);
        ui->lbl_protolDate->setText(date.toString("dd.MM.yyyy"));
        ui->lbl_protolNumber->setText(plan->protocolNumber());
    } else {
        ui->w_protocol->setVisible(false);
    }
}

void Header::setApproved(TeacherPlan *plan)
{
    auto date = plan->approveDate();
    // auto user = plan->approveUserId();

    if(date.isValid()){
        ui->lbl_approvedDate->setText(date.toString("dd.MM.yyyy"));
        //     if(user)
        //         ui->lbl_approvedName->setText(QString("%1 %2 %3.%4.")
        //                                           .arg(user->userData()->rang(),
        //                                                user->userData()->surname(),
        //                                                !user->userData()->name().isEmpty() ? user->userData()->name().at(0) : QString(),
        //                                                !user->userData()->middle_name().isEmpty() ? user->userData()->middle_name().at(0) : QString())
        //                                       );
    }
}

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

//void Header::savePlan()
//{
//    Database::get()->updateTeacherPlan(m_currentPlan);
//    m_currentPlan->setChanged(false);
//}

void Header::on_cb_department_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(!changeIndex(ui->cb_department))
        return;

    ui->cb_post->clear();

    auto userDep = ui->cb_department->currentData().toInt();
    auto userPosts = m_user->posts().values(userDep);

    foreach (auto post, m_posts) {
        if(userPosts.contains(post.id()))
            ui->cb_post->addItem(post.name(), post.id());
    }
}

void Header::on_cb_years_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(!changeIndex(ui->cb_years))
        return;

    setPlan();
}


void Header::on_cb_post_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(!changeIndex(ui->cb_post))
        return;

    setPlan();
}


void Header::setRate(double rate)
{
    m_currentPlan->setRate(rate);
    Database::get()->updateTeacherPlan(m_currentPlan);
}
