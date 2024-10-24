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

QPair<Hour, Hour> WeekEducationWork::totalValues() const
{
    // auto editors = findChildren<WeekValues*>();
    // H first, second;
    // auto m = Months::get();
    // for(WeekValues* editor : qAsConst(editors)){
    //     int week = editor->week();
    //     if(m->isFirstSemester(week)){
    //         first.plan = editor->planeValue();
    //         first.fact = editor->factValue();
    //     } else {
    //         second.plan = editor->planeValue();
    //         second.fact = editor->factValue();
    //     }
    // }
    // return qMakePair(first, second);
}

// QPair<int, int> WeekEducationWork::totalValue(HT type)
// {
//     auto list = type == HT::Plane ? m_planeFields : m_factFields;
//     int countFirst = 0;
//     int countSecond = 0;
//     for(auto l : list){
//         if(Months::get()->isFirstSemester(l->property("week").toInt()))
//             countFirst += l->text().toInt();
//         else
//             countSecond += l->text().toInt();
//     }

//     return qMakePair(countFirst, countSecond);
// }

// void WeekEducationWork::updateValue(QString text)
// {
//     auto editor = static_cast<QLineEdit*>(sender());
//     int val = text.toInt();
//     if(val == 0)
//         editor->setText("");
// }




//     emit valueChanged(0,HT::Plane, 0, 0);
//     emit valueChanged(0,HT::Factical, 0, 0);
// }



// void WeekEducationWork::setFieldType(QLineEdit * editor)
// {
//     QString name = editor->objectName();
//     bool isPLane = name.contains("plane");
//     editor->setProperty("is_plane", isPLane);
//     if(isPLane)
//         m_planeFields.append(editor);
//     else
//         m_factFields.append(editor);
// }

