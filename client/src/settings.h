#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QObject>

#include <misc/month.h>

class Settings : public QSettings
{
    Q_OBJECT

public:
    static Settings get();
    ~Settings() {};

    QString dbHost();
    void setDbHost(QString host);

    int dbPort();
    void setDbPort(int port);

    QString lastName();
    void setLastName(QString lastName);

    int weekCount(Month::Months month);
    QPair<int, int> weekDate(int week);

    int secondSemesterWeek();

private:
    Settings();

    template<typename  T>
    T get(const QString &key, const T &defValue = {}){
        QSettings s("settings.ini", QSettings::IniFormat);
        QVariant val = s.value(key, defValue);
        return val.value<T>();
    };

    template<typename  T>
    void set(const QString &key, const T &val){
        QSettings s("settings.ini", QSettings::IniFormat);
        s.setValue(key, val);
    };

    void loadWeeksCount();
    void loadWeeks();

    QMap<Month::Months, int> m_weekCount;
    QMap<int, QPair<int, int>> m_weeksDays;
    QMap<int, Month::Months> m_weeks;
};


#endif // SETTINGS_H
