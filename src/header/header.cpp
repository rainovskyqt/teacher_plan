#include "header.h"
#include "ui_header.h"

#include <QListView>
#include <QMessageBox>
#include <QDebug>

#include <user/usermanager.h>

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);
    this->setVisible(false);

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

    initModels();
    setTeacherData();

    ui->lbl_planNumbers->setVisible(false);
    ui->lbl_planNumbersText->setVisible(false);
    ui->sw_approved->setVisible(false);
    ui->w_protocol->setVisible(false);
}

void Header::setTeacher(int id)
{
    m_modelStaff.loadByUserId(id);
    init();
}

void Header::setDepartments(int index)
{
    ui->cb_department->clear();
    int id = m_modelYear.data(m_modelYear.index(index, DictionaryModel::ID)).toInt();
    auto deps = m_modelStaff.departments(id);
    for(auto it = deps.begin(); it != deps.end(); ++it)
        ui->cb_department->addItem(it.value(), it.key());
}

void Header::setPosts(int index)
{
    Q_UNUSED(index)
    ui->cb_post->clear();
    int id = ui->cb_department->currentData().toInt();
    auto posts = m_modelStaff.posts(id);
    for(auto it = posts.begin(); it != posts.end(); ++it)
        ui->cb_post->addItem(it.value(), it.key());
}

void Header::changePost(int index)
{
    if( index == -1 )
        return;
    int id = ui->cb_post->currentData().toInt();
        qDebug() << id;
    emit staffChanged(id);
}

void Header::initModels()
{
    initYearModel();
}

void Header::setTeacherData()
{
    ui->line_fio->setText(QString("%1 %2 %3").arg(m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserSurname)).toString(),
                                                  m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserName)).toString(),
                                                  m_modelStaff.data(m_modelStaff.index(0, ModelStaffList::UserMiddleName)).toString()));
}

void Header::initYearModel()
{
    ui->cb_years->setModel(&m_modelYear);
    ui->cb_years->setModelColumn(DictionaryModel::Name);
    connect(ui->cb_years , QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Header::setDepartments);
    setDepartments(0);
}

// User *Header::user() const
// {
//     return m_user;
// }

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

// void Header::setStaffData()
// {
//     auto d = m_user->userData();
//     ui->line_fio->setText(QString("%1 %2 %3 %4")
//                               .arg(d->rang(),
//                                    d->surname(),
//                                    d->name(),
//                                    d->middle_name()));
//     setUserDepartments();
// }

// void Header::loadData()
// {
//     DictionaryAdapter::setYears(ui->cb_years);
//     DictionaryAdapter::setDictionary(m_departments, Database::Department);
//     DictionaryAdapter::setDictionary(m_posts, Database::Post);
// }

// void Header::setDefaultData(int yearId)
// {
//     m_currentPlan = new TeacherPlan(this);
//     setStatus(TeacherPlan::Development);
//     m_currentPlan->setStatusId(TeacherPlan::Development);
//     m_currentPlan->setStaff(ui->cb_post->currentData().value<UserPost>());
//     m_currentPlan->setYearId(yearId);
//     ui->w_protocol->setVisible(false);

//     emit currentPlanChanged(m_currentPlan);
// }

// void Header::setCurrentIndexes()
// {
//     m_currentIndex.insert(ui->cb_years, -1);
//     m_currentIndex.insert(ui->cb_department, -1);
//     m_currentIndex.insert(ui->cb_post, -1);
// }

// bool Header::changeIndex(QComboBox *box)
// {
//     if(box->currentIndex() == m_currentIndex.value(box))
//         return false;


//     m_currentIndex.insert(box, box->currentIndex());

//     return true;
// }


// void Header::setUserDepartments()
// {
//     ui->cb_department->clear();

//     QList<int> userDep;
//     auto posts = m_user->posts();
//     for(auto p: posts)
//         userDep.append(p.departmentId);

//     foreach (auto dep, m_departments) {
//         if(userDep.contains(dep.id()))
//             ui->cb_department->addItem(dep.name(), dep.id());
//     }

// }

// void Header::setPlan()
// {
//     auto staff = ui->cb_post->currentData().value<UserPost>();
//     auto year = ui->cb_years->currentData().toInt();

//     setPlanData(Database::get()->requestPlan(staff, year));
// }

// QString Header::currentTecher()
// {
//     return ui->line_fio->text();
// }

// QString Header::currentDepartment()
// {
//     return ui->cb_department->currentText();
// }

// QString Header::currentYear()
// {
//     return ui->cb_years->currentText();
// }

// void Header::setUser(int id)
// {
//     setUser(Database::get()->login("", "", id));
// }

// void Header::setPlanData(TeacherPlan *plan)
// {
//     m_currentPlan = plan;
//     setStatus(m_currentPlan->statusId());
//     setProtocol(m_currentPlan);
//     setApproved(m_currentPlan);
//     qDebug() << "Загружен план с id: " << plan->baseId();

//     emit currentPlanChanged(m_currentPlan);
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

//void Header::savePlan()
//{
//    Database::get()->updateTeacherPlan(m_currentPlan);
//    m_currentPlan->setChanged(false);
//}

// void Header::on_cb_department_currentIndexChanged(int index)
// {
//     Q_UNUSED(index)

//     if(!changeIndex(ui->cb_department))
//         return;

//     ui->cb_post->clear();

//     auto userDep = ui->cb_department->currentData().toInt();
//     auto userPosts = m_user->posts();

//     for(auto userPost: userPosts) {
//         if(userPost.departmentId != userDep)
//             continue;
//         foreach(auto post, m_posts)
//             if(userPost.postId == post.id())
//                 ui->cb_post->addItem(post.name(), QVariant::fromValue(userPost));
//     }
// }

// void Header::on_cb_years_currentIndexChanged(int index)
// {
//     Q_UNUSED(index)

//     if(!changeIndex(ui->cb_years))
//         return;

//     setPlan();
// }


// void Header::on_cb_post_currentIndexChanged(int index)
// {
//     Q_UNUSED(index)

//     if(!changeIndex(ui->cb_post))
//         return;

//     setPlan();
// }


// void Header::setRate(double rate)
// {
//     m_currentPlan->setRate(rate);
//     Database::get()->updateTeacherPlan(m_currentPlan);
// }
