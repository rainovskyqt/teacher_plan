#include "settings.h"

Settings::Settings()
{

}

Settings Settings::get()
{
    return Settings();
}

QString Settings::dbHost()
{
   return get<QString>("dbHost", "127.0.0.1");
}

void Settings::setDbHost(QString host)
{
    set("dbHost", host);
}

int Settings::dbPort()
{
    return get<int>("dbPort", 3306);
}

void Settings::setDbPort(int port)
{
    set("dbPort", port);
}

QString Settings::lastName()
{
    return get<QString>("lastName", "");
}

void Settings::setLastName(QString lastName)
{
    set("lastName", lastName);
}
