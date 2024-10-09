#ifndef ROWEDUCATIONWORK_H
#define ROWEDUCATIONWORK_H

#include <QWidget>

#include "database/dictionary/modeldiscipline.h"
#include "database/dictionary/modelcourses.h"
#include "database/dictionary/modelworkform.h"

#include "modeleducationwork.h"

class QComboBox;

namespace Ui {
class RowEducationWork;
}

class RowEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit RowEducationWork(int position, const ModelEducationWork::EducationWork &work,
                              bool enabled = true, QWidget *parent = nullptr);
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

    ModelDiscipline m_disciplines;
    ModelCourses m_courses;
    ModelWorkForm m_workForm;
    ModelEducationWork::EducationWork m_work;

    void setModels();
    void setModel(QAbstractItemModel *model, QComboBox *cbox);
    void setWorkData(const ModelEducationWork::EducationWork &work);
    void setComboboxData(QAbstractItemModel *model, QComboBox *cbox, int vId);
    void setSaved(bool s);
};

#endif // ROWEDUCATIONWORK_H
