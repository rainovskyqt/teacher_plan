#ifndef PAGEEDUCATIONWORK_H
#define PAGEEDUCATIONWORK_H

#include <QWidget>

#include "modeleducationwork.h"

namespace Ui {
class PageEducationWork;
}

class PageEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit PageEducationWork(QWidget *parent = nullptr);
    ~PageEducationWork();

public slots:
    void setPlan(int planId);

private slots:
    void on_btn_add_clicked();
    void deleteRow();

    void on_btn_up_clicked();
    void on_btn_down_clicked();

private:
    Ui::PageEducationWork *ui;

    ModelEducationWork m_model;

    void fillTable();
    void addRow(int row, const ModelEducationWork::EducationWork &work);
    void clearData();
    void updateRowNumber(int start);
    void swapItems(int fromRow, int toRow);
};

#endif // PAGEEDUCATIONWORK_H
