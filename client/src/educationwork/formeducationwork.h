#ifndef FORMEDUCATIONWORK_H
#define FORMEDUCATIONWORK_H

#include <QWidget>

namespace Ui {
class FormEducationWork;
}

class FormEducationWork : public QWidget
{
    Q_OBJECT

public:
    explicit FormEducationWork(QWidget *parent = nullptr);
    ~FormEducationWork();

private:
    Ui::FormEducationWork *ui;

    void setTable();
};

#endif // FORMEDUCATIONWORK_H
