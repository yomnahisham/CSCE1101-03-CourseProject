QT       += core gui \
            multimedia \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allusers.cpp \
    fireboy.cpp \
    gameover.cpp \
    layout.cpp \
    level.cpp \
    loginwindow.cpp \
    main.cpp \
    obstacles.cpp \
    players.cpp \
    registerwindow.cpp \
    user.cpp \
    watergirl.cpp \
    windowmanager.cpp

HEADERS += \
    allusers.h \
    fireboy.h \
    gameover.h \
    layout.h \
    level.h \
    loginwindow.h \
    obstacles.h \
    players.h \
    registerwindow.h \
    user.h \
    watergirl.h \
    windowmanager.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Specify library search path
LIBS += -L/opt/homebrew/opt/sqlite/lib

# Specify include search path
INCLUDEPATH += /opt/homebrew/opt/sqlite/include

RESOURCES += \
    Resources.qrc

FORMS += \
    gameover.ui \
    level.ui \
    loginwindow.ui \
    registerwindow.ui
