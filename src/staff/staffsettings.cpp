#include "staffmanager.h"
#include "staffsettings.h"
#include "ui_staffsettings.h"

#include <user/usermanager.h>

#include <QPushButton>

#include <database/dictionary/dictionarymanager.h>

StaffSettings::StaffSettings(int staffId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StaffSettings)
    , m_staffId(staffId)
{
    ui->setupUi(this);

    init();
}

StaffSettings::~StaffSettings()
{
    delete ui;
}

void StaffSettings::init()
{
    setAdmin();
    setModels();
    setStaffData();

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &StaffSettings::saveStaff);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &StaffSettings::close);
}

void StaffSettings::setAdmin()
{
    bool admin = UserManager::get()->user()->isAdmin();
    ui->cb_department->setEnabled(admin);
    ui->cb_user->setEnabled(!m_staffId);
}

void StaffSettings::setModels()
{
    ui->cb_department->setModel(DictionaryManager::get()->departments());
    ui->cb_department->setModelColumn(DictionaryModel::Name);

    ui->cb_post->setModel(DictionaryManager::get()->posts());
    ui->cb_post->setModelColumn(DictionaryModel::Name);

    setUsers(UserManager::get()->allUserList());
}

void StaffSettings::setStaffData()
{
    if(!m_staffId)
        return;

    auto staff = StaffManager::get()->getStaff(m_staffId);

    if(staff == nullptr)
        return;

    setBoxData(ui->cb_department, staff->departmentId());
    setBoxData(ui->cb_post, staff->postId());
    ui->cb_rate->setCurrentText(QString::number(staff->rate()));
    ui->cb_user->setCurrentIndex(ui->cb_user->findData(staff->userId()));
}

void StaffSettings::setBoxData(QComboBox *box, int id)
{
    auto model = qobject_cast<DictionaryModel*>(box->model());
    int index = model->idRowIndex(id);
    box->setCurrentIndex(index);
}

int StaffSettings::getId(QComboBox *box)
{
    auto model = box->model();
    return model->data(model->index(box->currentIndex(), 0)).toInt();
}

void StaffSettings::saveStaff()
{
    auto userId = getId(ui->cb_user);
    auto depId = getId(ui->cb_department);
    auto postId = getId(ui->cb_post);
    auto rate = ui->cb_rate->currentText().toDouble();
    auto year = DictionaryManager::get()->years()->currentYearId();

    StaffManager::get()->saveStaff(userId, Staff(m_staffId, userId, depId, postId, rate, year));
    this->close();
}

void StaffSettings::setUsers(QVector<QPair<int, QString>> list)
{
    for(const auto &l : qAsConst(list)){
        ui->cb_user->addItem(l.second, l.first);
    }
}
