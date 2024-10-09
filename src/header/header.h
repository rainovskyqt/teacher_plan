#ifndef HEADER_H
#define HEADER_H

#include <QComboBox>
#include <QWidget>

// #include "database/database.h"
// #include "modelheader.h"
// #include "misc/uniquefilterproxymodel.h"

#include "database/dictionary/modelyear.h"
#include "database/dictionary/modeldepartment.h"
#include "database/dictionary/modelpost.h"
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

    // void setStatus(int status);
    // void setProtocol(TeacherPlan* plan);
    // void setApproved(TeacherPlan* plan);
//    bool saveQustion();
};

#endif // HEADER_H
