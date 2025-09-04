#ifndef HEADER_H
#define HEADER_H

#include <QComboBox>
#include <QWidget>

#include "QSortFilterProxyModel"

#include "staff/modelstafflist.h"

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

    QSortFilterProxyModel m_modelYear;
    ModelStaffList m_modelStaff;

    void setTeacherData();
};

#endif // HEADER_H
