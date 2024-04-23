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

private slots:
    void on_btn_approvedCancel_clicked();
    void on_btn_toApprove_clicked();
    void setStaffData();

private:
    Ui::Header *ui;

    void loadDictionaries();
    void loadDictionary(Database::Dictionary dictName, QMap<int, QString> dict);
};

#endif // HEADER_H
