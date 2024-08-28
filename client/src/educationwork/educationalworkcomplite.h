#ifndef EDUCATIONALWORKCOMPLITE_H
#define EDUCATIONALWORKCOMPLITE_H

#include <QHeaderView>
#include <QWidget>


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

private:
    Ui::EducationalWorkComplite *ui;

    void setHeader();
    void setColumns();
    void addColumn(QString text, int id = 0);
    void setRows();
    void addRow(QString text, int id = 0);
    void fillTable();
};

#endif // EDUCATIONALWORKCOMPLITE_H
