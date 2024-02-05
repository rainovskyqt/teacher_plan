#ifndef HEADER_H
#define HEADER_H

#include <QWidget>

namespace Ui {
class Header;
}

class Header : public QWidget
{
    Q_OBJECT

public:
    explicit Header(QWidget *parent = nullptr);
    ~Header();

private slots:
    void on_btn_approvedCancel_clicked();
    void on_btn_toApprove_clicked();

private:
    Ui::Header *ui;
};

#endif // HEADER_H
