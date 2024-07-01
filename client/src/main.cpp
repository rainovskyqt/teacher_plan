#include <QApplication>
#include <QMessageBox>

#include "login/login.h"
#include "database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // if(!Database::get()->init("127.0.0.1", 3306)){
    if(!Database::get()->init("10.0.2.18", 3306)){
        QMessageBox::critical(nullptr, "Ошибка базы", "При открытии базы данных произошла ошибка:\n" +
                              Database::get()->lastError());
        return 0;
    }

    Login l;
    l.show();
    return a.exec();
}
