#ifndef PAGEEDUCATIONWORK_H
#define PAGEEDUCATIONWORK_H

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


private slots:
    void on_btn_add_clicked();
    void deleteRow();
    void on_btn_up_clicked();
    void on_btn_down_clicked();

private:
    Ui::PageEducationWork *ui;

    ModelEducationWork m_model;
    RowEducationWork *m_header;
    RowEducationWork *m_footer;

    void addHeader();
    void addFooter();
    void fillTable();
    void addRow(int row, const ModelEducationWork::EducationWork &work);
    void clearData();
    void updateRowNumber(int start);
    void swapItems(int fromRow, int toRow);
    void updateRowsSizeHint();
};

#endif // PAGEEDUCATIONWORK_H
