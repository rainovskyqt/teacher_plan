#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include <QFile>

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

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "teacher_plan_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QFile styleFile(":/styles/styles/ligth.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);
    }

    Login l;
    l.show();
    return a.exec();
}
