#ifndef EDUCATIONALFOOTER_H
#define EDUCATIONALFOOTER_H

#include <QWidget>

namespace Ui {
class EducationalFooter;
}

class EducationalFooter : public QWidget
{
    Q_OBJECT

public:
    explicit EducationalFooter(QWidget *parent = nullptr);
    ~EducationalFooter();

    void setPosition(int val);

private:
    Ui::EducationalFooter *ui;
};

#endif // EDUCATIONALFOOTER_H
