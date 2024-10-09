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
    explicit RowEducationWork(int position, QWidget *parent = nullptr);
    ~RowEducationWork();

    static QSize rowSize();
    void setWorkData(EducationWork *work);

    QString toString() const;

    int id() const;
    int row() const;
    void setRow(int row);

signals:
    void deleteWork();
    void saveMainData();

private slots:
    void setDiscipline(int index);
    void setCourse(int index);
    void setWorkForm(int index);

private:
    Ui::RowEducationWork *ui;

    ModelDiscipline m_disciplines;
    ModelCourses m_courses;
    ModelWorkForm m_workForm;
    EducationWork *m_work;

    void setModels();
    void setModel(QAbstractItemModel *model, QComboBox *cbox);
    void setComboboxData(QAbstractItemModel *model, QComboBox *cbox, int vId);
    void setSaved(bool s);
    int getDictionaryId(QAbstractItemModel *model, int row);
    bool checkMainDataForSave();
};

#endif // ROWEDUCATIONWORK_H
