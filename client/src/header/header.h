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

    void init(int userId);

private slots:
    void on_btn_approvedCancel_clicked();
    void on_btn_toApprove_clicked();

private:
    Ui::Header *ui;

    void loadDictionaries();
    void loadDictionary(QComboBox *cb, Database::Dictionary dict);
};

#endif // HEADER_H
