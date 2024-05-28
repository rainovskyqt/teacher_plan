#ifndef HEADER_H
#define HEADER_H

#include <QComboBox>
#include <QWidget>

#include <database/database.h>

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
    void modelDataChanged();

private slots:
    void on_btn_approvedCancel_clicked();
    void on_btn_toApprove_clicked();
    void setStaffData();
    void on_cb_department_currentIndexChanged(int index);
    void on_cb_years_currentIndexChanged(int index);
    void on_cb_post_currentIndexChanged(int index);

signals:
    void currentPlanChanget(TeacherPlan*);

private:
    Ui::Header *ui;

    enum ApprovedPages{
        Development,
        OnApproved,
        Approveded
    };

    // int m_currentYear;
    // int m_currentDepartment;
    // int m_currentPost;

    QMap<QComboBox*, int> m_currentIndex;

    QList<Dictionary*> m_departments;
    QList<Dictionary*> m_posts;
    QList<StudyYear*> m_years;
    QList<TeacherPlan*> m_plans;
    TeacherPlan* m_currentPlan;

    void clearDicts();
    void loadData();
    void setDefaultData();
    void setCurrentIndexes();
    bool changeIndex(QComboBox *box);
    void loadDictionary(Database::DictName dictName, QList<Dictionary*> dict);
    void setUserDepartments();
    void setUserYears();
    void setPlanData();
    void setStatus(int status);
    void setProtocol(TeacherPlan* plan);
    void setApproved(TeacherPlan* plan);
    bool saveQustion();
    void save();
};

#endif // HEADER_H
