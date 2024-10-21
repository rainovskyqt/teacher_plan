#include "weekeducationwork.h"
#include "ui_weekeducationwork.h"

#include <QIntValidator>
#include <QLabel>
#include <QDebug>

WeekEducationWork::WeekEducationWork(const QHash<int, H> &hours, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekEducationWork)
{
    ui->setupUi(this);
    initFieds(hours);
}

WeekEducationWork::~WeekEducationWork()
{
    delete ui;
}

void WeekEducationWork::updateValue(QString text)
{
    auto editor = static_cast<QLineEdit*>(sender());
    int val = text.toInt();
    if(val == 0)
        editor->setText("");

    emit valueChanged(editor->property("id").value<int>(),
                      editor->property("type").value<HT>(),
                      val);
}

void WeekEducationWork::setClearingField(QLineEdit * editor)
{
    connect(editor, &QLineEdit::textChanged, this, &WeekEducationWork::updateValue);
    editor->setValidator(new QIntValidator(0, 1000, this));
}

void WeekEducationWork::setWeekProperty(QLineEdit * editor)
{
    QString name = editor->objectName();
    int week = name.rightRef(2).toInt();
    editor->setProperty("week", week);
}

void WeekEducationWork::setValues(QList<QLineEdit *>editors, const QHash<int, H> &hours)
{
    for(auto editor : qAsConst(editors)){
        int week = editor->property("week").toInt();
        H hour = hours.value(week);
        QString name = editor->objectName();
        bool isPLane = name.contains("plane");
        int value = isPLane ? hour.planValue : hour.factValue;
        editor->setText(QString::number(value));
        editor->setProperty("id", isPLane ? hour.planId : hour.factId);
    }
}

void WeekEducationWork::initFieds(const QHash<int, H> &hours)
{
    auto fields = findChildren<QLineEdit*>();
    for(auto f : fields){
        setClearingField(f);
        setWeekProperty(f);
    }

    setValues(fields, hours);
}

