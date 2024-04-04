QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abilities.cpp \
    allusers.cpp \
    fireboy.cpp \
    layout.cpp \
    level.cpp \
    loginwindow.cpp \
    main.cpp \
    obstacles.cpp \
    players.cpp \
    registerwindow.cpp \
    status.cpp \
    user.cpp \
    watergirl.cpp

HEADERS += \
    abilities.h \
    allusers.h \
    fireboy.h \
    layout.h \
    level.h \
    loginwindow.h \
    obstacles.h \
    players.h \
    registerwindow.h \
    status.h \
    user.h \
    watergirl.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

FORMS += \
    level.ui \
    loginwindow.ui \
    registerwindow.ui
