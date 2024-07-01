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
    void setValue(int value, QString name);
    void setTotalValue(int value, QString name);
    QStringList hourFields();
    QStringList totalFields();

signals:
    void firstPlaneChanget(int);
    void secondPlaneChanget(int);
    void firstFacticalChanget(int);
    void secondFacticalChanget(int);

private:
    Ui::EducationalFooter *ui;
    void sendSignal(QString name, int val);
};

#endif // EDUCATIONALFOOTER_H
