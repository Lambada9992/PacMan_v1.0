QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console  #konsola

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GAME/CHARACTER/gamecharacter.cpp \
    GAME/CHARACTER/ghost.cpp \
    GAME/CHARACTER/myplayer.cpp \
    GAME/CHARACTER/onlineplayer.cpp \
    GAME/CHARACTER/player.cpp \
    GAME/board.cpp \
    GAME/game.cpp \
    GUI/ITEM/gui_board.cpp \
    GUI/ITEM/gui_character.cpp \
    GUI/ITEM/mybonus.cpp \
    GUI/ITEM/mybutton.cpp \
    GUI/ITEM/myobstacle.cpp \
    GUI/gui_view.cpp \
    main.cpp

HEADERS += \ \
    GAME/CHARACTER/gamecharacter.h \
    GAME/CHARACTER/ghost.h \
    GAME/CHARACTER/myplayer.h \
    GAME/CHARACTER/onlineplayer.h \
    GAME/CHARACTER/player.h \
    GAME/board.h \
    GAME/game.h \
    GUI/ITEM/gui_board.h \
    GUI/ITEM/gui_character.h \
    GUI/ITEM/mybonus.h \
    GUI/ITEM/mybutton.h \
    GUI/ITEM/myobstacle.h \
    GUI/gui_view.h \
    game.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
