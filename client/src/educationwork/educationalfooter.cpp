#include "educationalfooter.h"
#include "ui_educationalfooter.h"
#include <QScrollBar>

EducationalFooter::EducationalFooter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EducationalFooter)
{
    ui->setupUi(this);
}

EducationalFooter::~EducationalFooter()
{
    delete ui;
}

void EducationalFooter::setPosition(int val)
{
    ui->scrollArea->horizontalScrollBar()->setValue(val);
}

void EducationalFooter::setValue(int value, QString name)
{
    auto current = this->findChildren<QLineEdit*>();

    foreach(auto l, current){
        if(l->objectName() == name){
            l->setText(value ? QString::number(value): "");
            break;
        }
    }
}

void EducationalFooter::setTotalValue(int value, QString name)
{
    auto current = this->findChildren<QLabel*>();

    foreach(auto l, current){
        if(l->objectName() == name){
            l->setText(value ? QString::number(value): "");
            break;
        }
    }
    sendSignal(name, value);
}

QStringList EducationalFooter::hourFields()
{
    QStringList lines;
    auto current = this->findChildren<QLineEdit*>();
    foreach(auto l, current){
        lines.append(l->objectName());
    }
    return lines;
}

QStringList EducationalFooter::totalFields()
{
    QStringList lbl;
    auto current = this->findChildren<QLabel*>();
    foreach(auto l, current){
        if(l->objectName().contains("label"))
            continue;
        lbl.append(l->objectName());
    }
    return lbl;
}

void EducationalFooter::sendSignal(QString name, int val)
{
    if(name == "lbl_firstPlan")
        emit firstPlaneChanget(val);
    else if (name == "lbl_secondPlan")
        emit secondPlaneChanget(val);
    else if (name == "lbl_firstFact")
        emit firstFacticalChanget(val);
    else if (name == "lbl_secondFact")
        emit secondFacticalChanget(val);
}
