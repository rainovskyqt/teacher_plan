#ifndef PAGEEDUCATIONWORK_H
#define PAGEEDUCATIONWORK_H

#include <QListWidgetItem>
#include <QWidget>

#include "educationwork.h"
#include "modeleducationwork.h"
#include "database/types.h"

class RowEducationWork;

namespace Ui {
class PageEducationWork;
}

class PageEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit PageEducationWork(QWidget *parent = nullptr);
    ~PageEducationWork();

    void resizeEvent(QResizeEvent *e);

public slots:
    void setPlan(int planId);
    void setOwnPlan(int staff);

signals:
    void clear();
    void totalChanged(WorkType, const TotalHour*);
    void rateChanged(double);

private slots:
    void deleteRow();
    void rowUp();
    void rowDown();
    void addNewRow();
    void updateValues(EducationWork *w, int week);
    void setSliderMaximum(int max);

private:
    Ui::PageEducationWork *ui;

    ModelEducationWork m_model;
    RowEducationWork *m_header;
    RowEducationWork *m_footer;
    QList<EducationWork*> m_edWorks;
    QMap<int, Hour*> m_totalHours;

    bool m_readySave;
    bool m_ownPlan;

    void addHeader();
    void addFooter();
    void fillTable(int staffId);
    void addRow(int row, EducationWork *work);
    void clearData();
    void updateRowNumber(int start);
    void swapItems(int fromRow, int toRow);
    void updateRowsSizeHint();
    void clearLayout(QLayout *la);
    void resetScrollbar();
    void updateTotal();
    void saveNewValue(EducationWork *w, int week);
    void updateOwn(bool own);
};

#endif // PAGEEDUCATIONWORK_H
