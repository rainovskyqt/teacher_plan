#include <QApplication>
#include <QMessageBox>
#include <settings.h>

#include "login/login.h"
#include "database/database.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!Database::get()->init(Settings::get().dbHost(), Settings::get().dbPort())){
        QMessageBox::critical(nullptr, "Ошибка базы", "При открытии базы данных произошла ошибка:\n" +
                              Database::get()->lastError());
        return 0;
    }
    Login l;
    l.show();
    return a.exec();
}
