#ifndef WEEKEDUCATIONWORK_H
#define WEEKEDUCATIONWORK_H

#include <QLineEdit>
#include <QWidget>

#include "modeleducationwork.h"

namespace Ui {
class WeekEducationWork;
}

class WeekEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit WeekEducationWork(const ModelEducationWork::Hour &hour, QWidget *parent = nullptr);
    ~WeekEducationWork();

signals:
    void valueChanged(ModelEducationWork::Hour);           //id, plane, fact

private slots:
    void clearField(QString text);
    void on_line_plane_textChanged(const QString &arg1);
    void on_line_fact_textChanged(const QString &arg1);

private:
    Ui::WeekEducationWork *ui;

    ModelEducationWork::Hour m_hour;

    void setClearingField(QLineEdit *editor);
};

#endif // WEEKEDUCATIONWORK_H
