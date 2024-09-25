#ifndef UPDATECOMMENTSROW_H
#define UPDATECOMMENTSROW_H

#include <QWidget>

namespace Ui {
class UpdateCommentsRow;
}

class UpdateCommentsRow : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateCommentsRow(int id, QString date, QString version, QString text, QWidget *parent = nullptr);
    ~UpdateCommentsRow();

    int baseId() const;

private:
    Ui::UpdateCommentsRow *ui;

    int m_baseId;
};

#endif // UPDATECOMMENTSROW_H
