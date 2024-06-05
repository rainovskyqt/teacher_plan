#include "header.h"
#include "ui_header.h"

#include <QListView>
#include <QMessageBox>


#include "login/user.h"

Header::Header(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Header)
{
    ui->setupUi(this);
    this->setVisible(false);
    // setDefaultData();
    ui->lbl_planNumbers->setVisible(false);
    ui->lbl_planNumbersText->setVisible(false);

    setCurrentIndexes();
}

Header::~Header()
{
    clearDicts();
    delete ui;
}

void Header::init()
{
    this->setVisible(true);

    loadData();
}

void Header::on_btn_approvedCancel_clicked()
{
    ui->sw_approved->setCurrentIndex(Development);
    m_currentPlan->setStatusId(TeacherPlan::Development);
    Database::get()->updateTeacherPlan(m_currentPlan);
}


void Header::on_btn_toApprove_clicked()
{
    ui->sw_approved->setCurrentIndex(OnApproved);
    m_currentPlan->setStatusId(TeacherPlan::OnApproved);
    Database::get()->updateTeacherPlan(m_currentPlan);
}

void Header::setStaffData()
{
    auto userData = User::get()->userData();
    ui->line_fio->setText(QString("%1 %2 %3 %4")
                              .arg(userData->rang(),
                                   userData->surname(),
                                   userData->name(),
                                   userData->middle_name()));
    setUserDepartments();
}

void Header::loadData()
{
    auto database = Database::get();

    connect(database, &Database::dictionary, this, &Header::loadDictionary);
    connect(database, &Database::years, this, [=](QList<StudyYear*> years){
        qDeleteAll(m_years);
        m_years = years;
        setUserYears();
    });
    connect(database, &Database::teacherPlans, this, [=](QList<PlansList*> plans){
        qDeleteAll(m_plans);
        m_plans = plans;
    });

    connect(database, &Database::planValues, this, &Header::setPlanData);
    connect(database, &Database::userDataLoaded, this, &Header::setStaffData);

    connect(database, &Database::newPlaneId, this, [&](int id){
        m_currentPlan->setBaseId(id);
        Database::get()->requestPlanValues(id);
    });

    int userId = User::get()->baseId();
    database->requestStaff(userId);
    database->requestDictionary(Database::Department);
    database->requestDictionary(Database::Post);
    database->requestYears();
    database->requestPlans(userId);
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

    QMap<int, PlanTime*> hours;
    hours.insert(1, new PlanTime(1, "Учебная работа", 0, 0, 0, 0, this));
    hours.insert(2, new PlanTime(2, "Учебно-методическая работа", 0, 0, 0, 0, this));
    hours.insert(3, new PlanTime(3, "Научно-исследовательская работа", 0, 0, 0, 0, this));
    hours.insert(4, new PlanTime(4, "Воспитательная и спортивная работа", 0, 0, 0, 0, this));
    hours.insert(5, new PlanTime(5, "Другие виды работ", 0, 0, 0, 0, this));

    m_currentPlan->setHours(hours);

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

    if(!saveQustion()){
        box->setCurrentIndex(m_currentIndex.value(box));
        return false;
    }

    m_currentIndex.insert(box, box->currentIndex());

    return true;
}

void Header::loadDictionary(Database::DictName dictName, QList<Dictionary*> dict)
{
    switch (dictName) {
    case Database::Department:
        qDeleteAll(m_departments);
        m_departments = dict;
        break;
    case Database::Post:
        qDeleteAll(m_posts);
        m_posts = dict;
        break;
    }
}

void Header::setUserDepartments()
{
    ui->cb_department->clear();

    auto userDep = User::get()->posts().keys();

    foreach (auto dep, m_departments) {
        if(userDep.contains(dep->id()))
            ui->cb_department->addItem(dep->name(), dep->id());
    }
}

void Header::setUserYears()
{
    ui->cb_years->clear();

    foreach (auto year, m_years) {
        ui->cb_years->addItem(QString("%1 - %2").arg(year->begin(), year->end()), year->id());
    }
}

void Header::setPlan()
{
    auto year = ui->cb_years->currentData().toInt();
    auto dep = ui->cb_department->currentData().toInt();
    auto post = ui->cb_post->currentData().toInt();

    bool load = false;
    foreach (auto plan, m_plans) {
        if(plan->year() == year && plan->department() == dep && plan->post() == post){
            qDebug() << "Загружен план с id: " << plan->id();
            Database::get()->requestPlanValues(plan->id());
            load = true;
            break;
        }
    }
    if(!load)
        setDefaultData( User::get()->baseId(), year, dep, post );
}

void Header::setPlanData(TeacherPlan *plan)
{
    m_currentPlan = plan;
    setStatus(m_currentPlan->statusId());
    setProtocol(m_currentPlan);
    setApproved(m_currentPlan);

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
    auto user = plan->approveUser();

    if(date.isValid()){
        ui->lbl_approvedDate->setText(date.toString("dd.MM.yyyy"));
        if(user)
            ui->lbl_approvedName->setText(QString("%1 %2 %3.%4.")
                                              .arg(user->userData()->rang(),
                                                   user->userData()->surname(),
                                                   !user->userData()->name().isEmpty() ? user->userData()->name().at(0) : QString(),
                                                   !user->userData()->middle_name().isEmpty() ? user->userData()->middle_name().at(0) : QString())
                                          );
    }
}

bool Header::saveQustion()
{
    if(!m_currentPlan || !m_currentPlan->isChanged())
        return true;

    int answer = QMessageBox::question(this, "Сохрание индивидуального плана", "Индивидуальный план был изменен, сохранить изменения?",
                                       QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    if(answer == QMessageBox::Cancel){
        return false;
    } else if(answer == QMessageBox::Yes) {
        savePlan();
    }
    m_currentPlan->setChanged(false);
    return true;
}

void Header::savePlan()
{
    Database::get()->updateTeacherPlan(m_currentPlan);
    m_currentPlan->setChanged(false);
}

void Header::on_cb_department_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(!changeIndex(ui->cb_department))
        return;

    ui->cb_post->clear();

    auto userDep = ui->cb_department->currentData().toInt();
    auto userPosts = User::get()->posts().values(userDep);

    foreach (auto post, m_posts) {
        if(userPosts.contains(post->id()))
            ui->cb_post->addItem(post->name(), post->id());
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
void Header::modelDataChanged()
{
    m_currentPlan->setChanged(true);
}

void Header::setRate(double rate)
{
    m_currentPlan->setRate(rate);
}

void Header::clearDicts()
{
    qDeleteAll(m_departments);
    qDeleteAll(m_posts);
    qDeleteAll(m_years);
    qDeleteAll(m_plans);
}

