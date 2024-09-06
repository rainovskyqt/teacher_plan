#ifndef EDUCATIONALWORKCOMPLITE_H
#define EDUCATIONALWORKCOMPLITE_H

#include <QHeaderView>
#include <QWidget>

#include <misc/month.h>


class CustomHeader : public QHeaderView {
public:
    CustomHeader(Qt::Orientation orientation, QWidget *parent = nullptr)
        : QHeaderView(orientation, parent) {}

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    QSize sizeHint() const override;
};


namespace Ui {
class EducationalWorkComplite;
}

class EducationalWorkComplite : public QWidget
{
    Q_OBJECT

public:
    explicit EducationalWorkComplite(QWidget *parent = nullptr);
    ~EducationalWorkComplite();

public slots:
    void setYearHours(int hours);
    void clearHours();

    void setFactValue(Month::Months month, int workForm, int value);

private slots:
    void on_tw_hours_cellChanged(int row, int column);

private:
    Ui::EducationalWorkComplite *ui;

    void setHeader();
    void setColumns();
    void addColumn(QString text, int id = 0);
    void setRows();
    void addRow(QString text, int id = 0);
    void fillTable();
    int getRowNumber(int month);
    int getColumnNumber(int workForm);
    void setRowCount(int row);
    void setColunmCount(int column);
    void checkTotalTime();
};

#endif // EDUCATIONALWORKCOMPLITE_H
