QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database.cpp \
    src/formeducationwork.cpp \
    src/formtotaltime.cpp \
    src/header.cpp \
    src/loginform.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/totaltimelist.cpp

HEADERS += \
    src/database.h \
    src/formeducationwork.h \
    src/formtotaltime.h \
    src/header.h \
    src/loginform.h \
    src/mainwindow.h \
    src/totaltimelist.h

FORMS += \
    src/formeducationwork.ui \
    src/formtotaltime.ui \
    src/header.ui \
    src/loginform.ui \
    src/mainwindow.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
