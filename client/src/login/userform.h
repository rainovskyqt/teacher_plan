#ifndef USERFORM_H
#define USERFORM_H

#include "user.h"

#include <QDialog>

#include <database/database.h>


namespace Ui {
class UserForm;
}

class UserForm : public QDialog
{
    Q_OBJECT

public:
    explicit UserForm(QWidget *parent = nullptr, User* user = nullptr);
    ~UserForm();

    User *newUser();

private:
    Ui::UserForm *ui;
    void loadData();
    void loadDictionary(Database::DictName dictName, QList<Dictionary*> dict);
};

#endif // USERFORM_H
