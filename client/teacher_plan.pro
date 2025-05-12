QT       += core gui sql network printsupport

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

VERSION = 0.0.1.9

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
    src/database/models/userrigth.cpp \
    src/educationwork/educationalfooter.cpp \
    src/educationwork/educationalhour.cpp \
    src/educationwork/educationalworkcomplite.cpp \
    src/educationwork/educationheader.cpp \
    src/educationwork/educationmonth.cpp \
    src/educationwork/educationmonthheader.cpp \
    src/educationwork/educationrow.cpp \
    src/educationwork/educationweek.cpp \
    src/educationwork/educationweekheader.cpp \
    src/educationwork/formeducationwork.cpp \
    src/faculty/facultypanel.cpp \
    src/generic/formgenerikwork.cpp \
    src/generic/genericfooter.cpp \
    src/generic/generikworkrow.cpp \
    src/header/headercombobox.cpp \
    src/login/login.cpp \
    src/login/user.cpp \
    src/login/userform.cpp \
    src/misc/combobox.cpp \
    src/misc/inplacefilter.cpp \
    src/misc/month.cpp \
    src/misc/wheelblocker.cpp \
    src/print/datafiles/printanalysisdata.cpp \
    src/print/datafiles/printcomplite.cpp \
    src/print/datafiles/printdata.cpp \
    src/print/datafiles/printgenericdata.cpp \
    src/print/datafiles/printstudydata.cpp \
    src/print/datafiles/printtitledata.cpp \
    src/print/datafiles/printtotaldata.cpp \
    src/print/genericworks/pagegenericwork.cpp \
    src/print/genericworks/pagemethodicwork.cpp \
    src/print/genericworks/pageotherwork.cpp \
    src/print/genericworks/pageresearchingwork.cpp \
    src/print/genericworks/pagesportwork.cpp \
    src/print/pageanalysis.cpp \
    src/print/pagecomplete.cpp \
    src/print/pagestudy.cpp \
    src/print/pagetitle.cpp \
    src/print/pagetotal.cpp \
    src/print/printform.cpp \
    src/print/printpage.cpp \
    src/settings.cpp \
    src/header/header.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/totaltime/formtotaltime.cpp \
    src/updatecomments/updatecommentsrow.cpp \
    src/updatecomments/updatecomments.cpp \

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
    src/database/models/userrigth.h \
    src/educationwork/educationalfooter.h \
    src/educationwork/educationalhour.h \
    src/educationwork/educationalworkcomplite.h \
    src/educationwork/educationheader.h \
    src/educationwork/educationmonth.h \
    src/educationwork/educationmonthheader.h \
    src/educationwork/educationrow.h \
    src/educationwork/educationweek.h \
    src/educationwork/educationweekheader.h \
    src/educationwork/formeducationwork.h \
    src/faculty/facultypanel.h \
    src/generic/formgenerikwork.h \
    src/generic/genericfooter.h \
    src/generic/generikworkrow.h \
    src/header/headercombobox.h \
    src/login/login.h \
    src/login/user.h \
    src/login/userform.h \
    src/misc/combobox.h \
    src/misc/inplacefilter.hpp \
    src/misc/month.h \
    src/misc/wheelblocker.hpp \
    src/print/datafiles/printanalysisdata.h \
    src/print/datafiles/printcomplite.h \
    src/print/datafiles/printdata.h \
    src/print/datafiles/printgenericdata.h \
    src/print/datafiles/printstudydata.h \
    src/print/datafiles/printtitledata.h \
    src/print/datafiles/printtotaldata.h \
    src/print/genericworks/pagegenericwork.h \
    src/print/genericworks/pagemethodicwork.h \
    src/print/genericworks/pageotherwork.h \
    src/print/genericworks/pageresearchingwork.h \
    src/print/genericworks/pagesportwork.h \
    src/print/pageanalysis.h \
    src/print/pagecomplete.h \
    src/print/pagestudy.h \
    src/print/pagetitle.h \
    src/print/pagetotal.h \
    src/print/printform.h \
    src/print/printpage.h \
    src/settings.h \
    src/header/header.h \
    src/mainwindow.h \
    src/totaltime/formtotaltime.h \
    src/totaltime/status.h \
    src/updatecomments/updatecommentsrow.h \
    src/updatecomments/updatecomments.h

FORMS += \
    src/educationwork/educationalfooter.ui \
    src/educationwork/educationalworkcomplite.ui \
    src/educationwork/educationheader.ui \
    src/educationwork/educationmonth.ui \
    src/educationwork/educationmonthheader.ui \
    src/educationwork/educationrow.ui \
    src/educationwork/educationweek.ui \
    src/educationwork/educationweekheader.ui \
    src/educationwork/formeducationwork.ui \
    src/faculty/facultypanel.ui \
    src/generic/formgenerikwork.ui \
    src/generic/genericfooter.ui \
    src/generic/generikworkrow.ui \
    src/login/login.ui \
    src/login/userform.ui \
    src/header/header.ui \
    src/mainwindow.ui \
    src/print/printform.ui \
    src/print/printpage.ui \
    src/totaltime/formtotaltime.ui \
    src/updatecomments/updatecommentsrow.ui \
    src/updatecomments/updatecomments.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
