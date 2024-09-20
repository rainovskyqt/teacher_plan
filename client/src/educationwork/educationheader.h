#ifndef EDUCATIONHEADER_H
#define EDUCATIONHEADER_H

#include <QMap>
#include <QWidget>

namespace Ui {
class EducationHeader;
}

class EducationHeader : public QWidget
{
    Q_OBJECT

public:

    explicit EducationHeader(QWidget *parent = nullptr);
    ~EducationHeader();
    int maximumPosition();

    int timeAreaWidth();

public slots:
    void setPosition(int val);

private:
    Ui::EducationHeader *ui;

    void addMonths();
};

#endif // EDUCATIONHEADER_H
