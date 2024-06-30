QT       += core gui sql network

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/database/adapters/dictionaryadapter.cpp \
    src/database/database.cpp \
    src/database/models/educationalwork.cpp \
    src/database/models/plantime.cpp \
    src/database/models/teacherplan.cpp \
    src/database/models/userdata.cpp \
    src/educationwork/educationheader.cpp \
    src/educationwork/educationrow.cpp \
    src/educationwork/formeducationwork.cpp \
    src/header/headercombobox.cpp \
    src/login/login.cpp \
    src/login/user.cpp \
    src/login/userform.cpp \
    src/misc/HierarchicalHeaderView.cpp \
    src/totaltime/formtotaltime.cpp \
    src/totaltime/modeltotaltime.cpp \
    src/header/header.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/database/adapters/dictionaryadapter.h \
    src/database/database.h \
    src/database/models/datamodels.h \
    src/database/models/educationalwork.h \
    src/database/models/plantime.h \
    src/database/models/teacherplan.h \
    src/database/models/userdata.h \
    src/educationwork/educationheader.h \
    src/educationwork/educationrow.h \
    src/educationwork/formeducationwork.h \
    src/header/headercombobox.h \
    src/login/login.h \
    src/login/user.h \
    src/login/userform.h \
    src/misc/HierarchicalHeaderView.h \
    src/totaltime/formtotaltime.h \
    src/totaltime/modeltotaltime.h \
    src/header/header.h \
    src/mainwindow.h \
    src/totaltime/status.h

FORMS += \
    src/educationwork/educationheader.ui \
    src/educationwork/educationrow.ui \
    src/educationwork/formeducationwork.ui \
    src/login/login.ui \
    src/login/userform.ui \
    src/totaltime/formtotaltime.ui \
    src/header/header.ui \
    src/mainwindow.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
