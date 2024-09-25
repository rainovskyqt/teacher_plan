#ifndef UPDATECOMMENTS_H
#define UPDATECOMMENTS_H

#include <QDialog>
#include "database/models/datamodels.h"

namespace Ui {
class UpdateComments;
}

class UpdateComments : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateComments(QWidget *parent = nullptr);
    ~UpdateComments();

    bool loadComments(int userId, bool all = false);
    bool dontShow();
    void setViewed();

private:
    Ui::UpdateComments *ui;

    int m_userId;

    void setComments(QMap<int, CommentsUpdate> comments);
    void addRow(int id, QString date, QString version, QString comments);
};

#endif // UPDATECOMMENTS_H
