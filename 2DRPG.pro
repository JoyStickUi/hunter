#-------------------------------------------------
#
# Project created by QtCreator 2020-04-06T15:28:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2DRPG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += static

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    game.cpp \
    gamescene.cpp \
    gameobject.cpp \
    player.cpp \
    enemy.cpp \
    background.cpp \
    textures.cpp \
    gamemap.cpp \
    spritecoords.cpp \
    objectsdrawer.cpp \
    item.cpp \
    battle_ui.cpp \
    trader.cpp \
    trader_ui.cpp \
    notifications.cpp \
    skillbook.cpp \
    stat_ui.cpp \
    portal.cpp \
    potion.cpp \
    inventory_ui.cpp \
    questlogger.cpp \
    quest.cpp \
    button.cpp \
    menuscene.cpp

HEADERS += \
        mainwindow.h \
    game.h \
    gamescene.h \
    gameobject.h \
    player.h \
    enemy.h \
    background.h \
    textures.h \
    gamemap.h \
    spritecoords.h \
    objectsdrawer.h \
    item.h \
    battle_ui.h \
    trader.h \
    trader_ui.h \
    notifications.h \
    skillbook.h \
    stat_ui.h \
    portal.h \
    potion.h \
    inventory_ui.h \
    questlogger.h \
    quest.h \
    button.h \
    menuscene.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    files.qrc
