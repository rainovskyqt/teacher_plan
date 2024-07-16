#ifndef EDUCATIONALWORKCOMPLITE_H
#define EDUCATIONALWORKCOMPLITE_H

#include <QWidget>

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

private:
    Ui::EducationalWorkComplite *ui;
};

#endif // EDUCATIONALWORKCOMPLITE_H
