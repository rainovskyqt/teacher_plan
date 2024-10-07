#ifndef HEADER_H
#define HEADER_H

#include <QComboBox>
#include <QWidget>

// #include "database/database.h"
// #include "modelheader.h"
// #include "misc/uniquefilterproxymodel.h"

#include "staff/modelyear.h"
#include "staff/modeldepartment.h"
#include "staff/modelpost.h"
#include "staff/modelstafflist.h"
#include "QSortFilterProxyModel"

namespace Ui {
class Header;
}

class Header : public QWidget
{
    Q_OBJECT

public:
    explicit Header(QWidget *parent = nullptr);
    ~Header();

    void init();

    // User *user() const;
    // void setUser(User *newUser);
    // void setPlan();

    // QString currentTecher();
    // QString currentDepartment();
    // QString currentYear();

public slots:
    void setTeacher(int id);

private slots:
    void setDepartments(int index);
    void setPosts(int index);
    void changePost(int index);

    // void on_btn_approvedCancel_clicked();
    // void on_btn_toApprove_clicked();


signals:
    void staffChanged(int);

private:
    Ui::Header *ui;

    enum ApprovedPages{
        Development,
        OnApproved,
        Approveded
    };

    ModelYear m_modelYear;
    ModelStaffList m_modelStaff;

    void setTeacherData();

    void initModels();
    void initYearModel();



    // void setUserDepartments();
    // void setPlanData(TeacherPlan *plan);
    // void setStatus(int status);
    // void setProtocol(TeacherPlan* plan);
    // void setApproved(TeacherPlan* plan);
//    bool saveQustion();
};

#endif // HEADER_H
