#include "updatecomments.h"
#include "ui_updatecomments.h"
#include "updatecommentsrow.h"

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
    auto commentId = ui->listWidget->item(ui->listWidget->count() - 1)->data(Qt::UserRole).toInt();
    Database::get()->setViewed(m_userId, commentId);
}

void UpdateComments::setComments(QMap<int, CommentsUpdate> comments)
{
    auto it = comments.constEnd();
    while (it != comments.constBegin()) {
        --it;

        auto item = new QListWidgetItem(ui->listWidget);
        item->setData(Qt::UserRole, it.value().id);
        auto row = new UpdateCommentsRow(it.value().id, it.value().date, it.value().version, it.value().comments);
        item->setSizeHint(row->sizeHint());
        ui->listWidget->setItemWidget(item, row);
    }
}
