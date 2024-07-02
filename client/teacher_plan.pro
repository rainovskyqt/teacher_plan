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
    src/database/models/genericwork.cpp \
    src/database/models/genericworkform.cpp \
    src/database/models/plantime.cpp \
    src/database/models/teacherplan.cpp \
    src/database/models/teacherwork.cpp \
    src/database/models/userdata.cpp \
    src/educationwork/educationalfooter.cpp \
    src/educationwork/educationalhour.cpp \
    src/educationwork/educationheader.cpp \
    src/educationwork/educationrow.cpp \
    src/educationwork/formeducationwork.cpp \
    src/generic/formgenerikwork.cpp \
    src/generic/genericfooter.cpp \
    src/generic/generikworkrow.cpp \
    src/header/headercombobox.cpp \
    src/login/login.cpp \
    src/login/user.cpp \
    src/login/userform.cpp \
    src/misc/HierarchicalHeaderView.cpp \
    src/totaltime/formtotaltime.cpp \
    src/header/header.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/database/adapters/dictionaryadapter.h \
    src/database/database.h \
    src/database/models/datamodels.h \
    src/database/models/educationalwork.h \
    src/database/models/genericwork.h \
    src/database/models/genericworkform.h \
    src/database/models/plantime.h \
    src/database/models/teacherplan.h \
    src/database/models/teacherwork.h \
    src/database/models/userdata.h \
    src/educationwork/educationalfooter.h \
    src/educationwork/educationalhour.h \
    src/educationwork/educationheader.h \
    src/educationwork/educationrow.h \
    src/educationwork/formeducationwork.h \
    src/generic/formgenerikwork.h \
    src/generic/genericfooter.h \
    src/generic/generikworkrow.h \
    src/header/headercombobox.h \
    src/login/login.h \
    src/login/user.h \
    src/login/userform.h \
    src/misc/HierarchicalHeaderView.h \
    src/totaltime/formtotaltime.h \
    src/header/header.h \
    src/mainwindow.h \
    src/totaltime/status.h

FORMS += \
    src/educationwork/educationalfooter.ui \
    src/educationwork/educationheader.ui \
    src/educationwork/educationrow.ui \
    src/educationwork/formeducationwork.ui \
    src/generic/formgenerikwork.ui \
    src/generic/genericfooter.ui \
    src/generic/generikworkrow.ui \
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
