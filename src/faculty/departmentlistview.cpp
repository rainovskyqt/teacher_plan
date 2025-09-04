#include "departmentlistview.h"

DepartmentListView::DepartmentListView(QWidget *parent) : QListView(parent)
{}

void DepartmentListView::selectDepartment(int depId)
{
    for(int row = 0; row < model()->rowCount(); ++row){
        if(model()->data(model()->index(row, 0)).toInt() == depId){
            QItemSelection sel(model()->index(row, 0), model()->index(row, model()->columnCount() - 1));
            selectionModel()->select(sel, QItemSelectionModel::Select);
        }
    }
}
