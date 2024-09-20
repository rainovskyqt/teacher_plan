#ifndef FACULTYPANEL_H
#define FACULTYPANEL_H

#include <QWidget>

#include <login/user.h>

namespace Ui {
class FacultyPanel;
}

class FacultyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FacultyPanel(QWidget *parent = nullptr);
    ~FacultyPanel();

    void setUser(User *newUser);

private:
    Ui::FacultyPanel *ui;

    User *m_user ;

    void setVisibility();
    void setFaculty();
};

#endif // FACULTYPANEL_H
