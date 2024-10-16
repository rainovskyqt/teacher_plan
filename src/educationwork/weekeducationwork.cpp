#include "weekeducationwork.h"
#include "ui_weekeducationwork.h"

#include <QIntValidator>

WeekEducationWork::WeekEducationWork(ModelEducationWork::Hour hour, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WeekEducationWork)
    , m_id{0}
{
    ui->setupUi(this);
    m_id = hour.id;

    setClearingField(ui->line_plane);
    setClearingField(ui->line_fact);

    ui->line_plane->setText(QString::number(hour.planValue));
    ui->line_fact->setText(QString::number(hour.factValue));
}

WeekEducationWork::~WeekEducationWork()
{
    delete ui;
}

void WeekEducationWork::clearField(QString text)
{
    auto editor = static_cast<QLineEdit*>(sender());
    if(text.toInt() == 0)
        editor->setText("");
}

void WeekEducationWork::setClearingField(QLineEdit *editor)
{
    connect(editor, &QLineEdit::textChanged, this, &WeekEducationWork::clearField);
    editor->setValidator(new QIntValidator(0, 1000, this));
}
