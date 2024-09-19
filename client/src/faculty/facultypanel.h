#ifndef FACULTYPANEL_H
#define FACULTYPANEL_H

#include <QWidget>

namespace Ui {
class FacultyPanel;
}

class FacultyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FacultyPanel(QWidget *parent = nullptr);
    ~FacultyPanel();

private:
    Ui::FacultyPanel *ui;
};

#endif // FACULTYPANEL_H
