#include "weekeducationwork.h"
#include "ui_weekeducationwork.h"

#include <QIntValidator>
#include "misc/months.h"
#include <QLabel>
#include <QDebug>

WeekEducationWork::WeekEducationWork(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekEducationWork)
{
    ui->setupUi(this);
    initFieds();
}

WeekEducationWork::~WeekEducationWork()
{
    delete ui;
}

QPair<int, int> WeekEducationWork::totalValue(HT type)
{
    auto list = type == HT::Plane ? m_planeFields : m_factFields;
    int countFirst = 0;
    int countSecond = 0;
    for(auto l : list){
        if(Months::get()->isFirstSemester(l->property("week").toInt()))
            countFirst += l->text().toInt();
        else
            countSecond += l->text().toInt();
    }

    return qMakePair(countFirst, countSecond);
}

void WeekEducationWork::updateValue(QString text)
{
    auto editor = static_cast<QLineEdit*>(sender());
    int val = text.toInt();
    if(val == 0)
        editor->setText("");

    emit valueChanged(editor->property("id").toInt(),
                      editor->property("type").value<HT>(),
                      val,
                      editor->property("week").toInt());
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

void WeekEducationWork::setValues(const QHash<int, H> &hours)
{
    auto editors = findChildren<QLineEdit*>();
    for(auto editor : qAsConst(editors)){
        int week = editor->property("week").toInt();
        H hour = hours.value(week);
        bool isPLane = editor->property("is_plane").toBool();
        int value = isPLane ? hour.planValue : hour.factValue;
        editor->setText(QString::number(value));
        editor->setProperty("id", isPLane ? hour.planId : hour.factId);
    }

    emit valueChanged(0,HT::Plane, 0, 0);
    emit valueChanged(0,HT::Factical, 0, 0);
}

void WeekEducationWork::initFieds()
{
    auto fields = findChildren<QLineEdit*>();
    for(auto f : fields){
        setFieldType(f);
        setClearingField(f);
        setWeekProperty(f);
    }
}

void WeekEducationWork::setFieldType(QLineEdit * editor)
{
    QString name = editor->objectName();
    bool isPLane = name.contains("plane");
    editor->setProperty("is_plane", isPLane);
    if(isPLane)
        m_planeFields.append(editor);
    else
        m_factFields.append(editor);
}

