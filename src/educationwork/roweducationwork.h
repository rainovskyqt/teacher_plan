#ifndef ROWEDUCATIONWORK_H
#define ROWEDUCATIONWORK_H

#include <QWidget>

#include <QSortFilterProxyModel>
#include "modeleducationwork.h"

class QComboBox;

namespace Ui {
class RowEducationWork;
}

class RowEducationWork : public QWidget
{
    Q_OBJECT

public:
    enum class Position{
        Row,
        Header,
        Footer
    };

    explicit RowEducationWork(int position, const ModelEducationWork::EducationWork &work,
                              Position pos = Position::Row, bool enabled = true, QWidget *parent = nullptr);
    ~RowEducationWork();

    QString toString() const;

    int id() const;
    int row() const;
    void setRow(int row);
    ModelEducationWork::EducationWork work() const;

signals:
    void deleteWork();

private:
    Ui::RowEducationWork *ui;

    QSortFilterProxyModel m_disciplines;
    QSortFilterProxyModel m_courses;
    QSortFilterProxyModel m_workForm;
    ModelEducationWork::EducationWork m_work;

    void setModels();
    void setModel(QAbstractItemModel *model, QSortFilterProxyModel *proxy, QComboBox *cbox);
    void setWorkData(const ModelEducationWork::EducationWork &work);
    void setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId);
    void setSaved(bool s);

    bool setRow(Position pos);
};

#endif // ROWEDUCATIONWORK_H
