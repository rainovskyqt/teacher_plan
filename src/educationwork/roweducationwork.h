#ifndef ROWEDUCATIONWORK_H
#define ROWEDUCATIONWORK_H

#include <QWidget>

#include <misc/emptylbl.h>

#include <QSortFilterProxyModel>
#include "modeleducationwork.h"
#include "weekeducationwork.h"
#include "database/types.h"

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

    explicit RowEducationWork(int number, Position position = Position::Row,
                              bool readOnly = false, QWidget *parent = nullptr);
    ~RowEducationWork();

    QString toString() const;

    int id() const;
    int row() const;
    void setRow(int row);
    EducationWork *work() const;
    void setWorkData(EducationWork *work);
    int sliderWight();
    void setHours(QMap<int, Hour *> hours);

public slots:
    void setSliderPosition(int pos);
    void setWidht(int widht);
    void setReadOnly(bool read);

signals:
    void deleteWork();
    void widhtChanged(int);
    void rowUpClicked();
    void rowDownClicked();
    void addNewRow();
    void valueChanged(EducationWork *w, int);
    void totalChanged(WorkType, const TotalHour*);
    void sliderMaximum(int);

private slots:
    void updateValues(int week);

protected:
    void resizeEvent(QResizeEvent *e);

private:
    Ui::RowEducationWork *ui;

    int m_row;

    const WorkType m_workType;
    QSortFilterProxyModel m_disciplines;
    QSortFilterProxyModel m_courses;
    QSortFilterProxyModel m_workForm;

    EducationWork *m_work;

    EmptyLbl* m_firstPlan;
    EmptyLbl* m_secondPlan;
    EmptyLbl* m_firstFact;
    EmptyLbl* m_secondFact;
    EmptyLbl* m_totalPlan;
    EmptyLbl* m_totalFact;

    TotalHour m_totalHours;
    bool m_readOnly;

    void setModels();
    void setModel(QAbstractItemModel *model, QSortFilterProxyModel *proxy, QComboBox *cbox);
    void setComboboxData(QSortFilterProxyModel *model, QComboBox *cbox, int vId);
    void setSaved(bool s);

    void setPosition(Position pos, int number);
    void setAsHeader();
    void setAsRow(int number);
    void addWeeks(QWidget *w);
    void setAsFooter();
    void setTotal();
};

#endif // ROWEDUCATIONWORK_H
