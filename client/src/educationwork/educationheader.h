#ifndef EDUCATIONHEADER_H
#define EDUCATIONHEADER_H

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

public slots:
    void setPosition(int val);

private:
    Ui::EducationHeader *ui;
};

#endif // EDUCATIONHEADER_H
