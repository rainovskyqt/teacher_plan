#ifndef STAFFSETTINGS_H
#define STAFFSETTINGS_H

#include <QComboBox>
#include <QDialog>

namespace Ui {
class StaffSettings;
}

class StaffSettings : public QDialog
{
    Q_OBJECT

public:
    explicit StaffSettings(int staffId, QWidget *parent = nullptr);
    ~StaffSettings();

private:
    Ui::StaffSettings *ui;

    void init();
    void setAdmin();
    void setModels();
    void setStaffData();
    void setBoxData(QComboBox *box, int id);
    int getId(QComboBox *box);
    void saveStaff();
    void setUsers(QVector<QPair<int, QString> > list);

    const int m_staffId;
};

#endif // STAFFSETTINGS_H
