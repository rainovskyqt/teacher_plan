#ifndef PAGEEDUCATIONWORK_H
#define PAGEEDUCATIONWORK_H

#include <QListWidgetItem>
#include <QWidget>

#include "modeleducationwork.h"

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

signals:
    void clear();

private slots:
    void deleteRow();
    void rowUp();
    void rowDown();
    void addNewRow();

private:
    Ui::PageEducationWork *ui;

    ModelEducationWork m_model;
    RowEducationWork *m_header;
    RowEducationWork *m_footer;

    bool m_readySave;

    void addHeader();
    void addFooter();
    void fillTable();
    void addRow(int row, const ModelEducationWork::EducationWork &work);
    void clearData();
    void updateRowNumber(int start);
    void swapItems(int fromRow, int toRow);
    void updateRowsSizeHint();
    void clearLayout(QLayout *la);
};

#endif // PAGEEDUCATIONWORK_H
