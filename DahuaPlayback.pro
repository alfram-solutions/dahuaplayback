QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11
CONFIG  += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    utility/Profile.cpp \
    utility/dhmutex.cpp

HEADERS += \
    UserDefine.h \
    libraries/dahua/avglobal.h \
    libraries/dahua/dhconfigsdk.h \
    libraries/dahua/dhnetsdk.h \
    mainwindow.hpp \
    utility/Profile.h \
    utility/dhmutex.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    DahuaPlayback_hi_IN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/libraries/dahua/ -lavnetsdk

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

unix:!macx: LIBS += -L$$PWD/libraries/dahua/ -ldhconfigsdk

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

unix:!macx: LIBS += -L$$PWD/libraries/dahua/ -ldhnetsdk

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/dahua/release/ -lInfra
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/dahua/debug/ -lInfra
else:unix: LIBS += -L$$PWD/libraries/dahua/ -lInfra

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/dahua/release/ -lNetFramework
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/dahua/debug/ -lNetFramework
else:unix: LIBS += -L$$PWD/libraries/dahua/ -lNetFramework

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/dahua/release/ -lNetFramework_ssl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/dahua/debug/ -lNetFramework_ssl
else:unix: LIBS += -L$$PWD/libraries/dahua/ -lNetFramework_ssl

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/dahua/release/ -lStream
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/dahua/debug/ -lStream
else:unix: LIBS += -L$$PWD/libraries/dahua/ -lStream

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libraries/dahua/release/ -lStreamSvr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libraries/dahua/debug/ -lStreamSvr
else:unix: LIBS += -L$$PWD/libraries/dahua/ -lStreamSvr

INCLUDEPATH += $$PWD/libraries/dahua
DEPENDPATH += $$PWD/libraries/dahua

DISTFILES += \
    config.ini \
    libraries/dahua/libInfra.so \
    libraries/dahua/libNetFramework.so \
    libraries/dahua/libNetFramework_ssl.so \
    libraries/dahua/libStream.so \
    libraries/dahua/libStreamSvr.so \
    libraries/dahua/libavnetsdk.so \
    libraries/dahua/libdhconfigsdk.so \
    libraries/dahua/libdhnetsdk.so

unix:!macx: LIBS += -lvlc
