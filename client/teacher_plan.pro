QT       += core gui

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database/database.cpp \
    src/educationwork/formeducationwork.cpp \
    src/totaltime/formtotaltime.cpp \
    src/totaltime/totaltimelist.cpp \
    src/header/header.cpp \
    src/login/loginform.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/database/database.h \
    src/educationwork/formeducationwork.h \
    src/totaltime/formtotaltime.h \
    src/totaltime/totaltimelist.h \
    src/header/header.h \
    src/login/loginform.h \
    src/mainwindow.h

FORMS += \
    src/educationwork/formeducationwork.ui \
    src/totaltime/formtotaltime.ui \
    src/header/header.ui \
    src/login/loginform.ui \
    src/mainwindow.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
