#include "weekeducationwork.h"
#include "ui_weekeducationwork.h"

#include "misc/months.h"

WeekEducationWork::WeekEducationWork(bool planeActive, bool factActive, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekEducationWork)
{
    ui->setupUi(this);
    initFieds(planeActive, factActive);
}

WeekEducationWork::~WeekEducationWork()
{
    delete ui;
}

void WeekEducationWork::initFieds(bool planeReadOnly, bool factReadOnly)
{
    auto fields = findChildren<WeekValues*>();
    for(auto f : fields){
        setWeekProperty(f);
        f->setPlaneReadOnly(planeReadOnly);
        f->setFactReadOnly(factReadOnly);
    }
}

void WeekEducationWork::setWeekProperty(WeekValues * editor)
{
    QString name = editor->objectName();
    int week = name.rightRef(2).toInt();
    editor->setWeek(week);
}

void WeekEducationWork::setValues(const QHash<int, Hour*> &hours)
{
    auto editors = findChildren<WeekValues*>();
    for(auto editor : qAsConst(editors)){
        int week = editor->week();
        auto val = hours.value(week);
        if(val)
            editor->setWeekValues(val);
        connect(editor, &WeekValues::valueUpdated, this, &WeekEducationWork::valueChanged);
    }
}
