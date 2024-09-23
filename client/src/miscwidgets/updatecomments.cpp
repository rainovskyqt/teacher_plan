#include "updatecomments.h"
#include "ui_updatecomments.h"

#include "database/database.h"

UpdateComments::UpdateComments(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateComments)
{
    ui->setupUi(this);
}

UpdateComments::~UpdateComments()
{
    delete ui;
}

bool UpdateComments::loadComments(int userId, bool all)
{
    auto c = Database::get()->updateComments(all, userId);
    m_userId = userId;

    if(c.count()){
        setComments(c);
        return true;
    }

    return false;
}

bool UpdateComments::dontShow()
{
    return ui->cb_dontShow->isChecked();
}

void UpdateComments::setViewed()
{
    auto commentId = ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->data(Qt::UserRole).toInt();
    Database::get()->setViewed(m_userId, commentId);
}

void UpdateComments::setComments(QMap<int, CommentsUpdate> comments)
{
    auto it = comments.constEnd();
    while (it != comments.constBegin()) {
        --it;

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        QTableWidgetItem *item = new QTableWidgetItem(it.value().date.toString("dd.MM.yyyy"));
        item->setData(Qt::UserRole, it.value().id);
        ui->tableWidget->setItem(row, 0, item);

        item = new QTableWidgetItem(it.value().version);
        ui->tableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(it.value().comments);
        ui->tableWidget->setItem(row, 2, item);
    }
}
