QT += quick \
      multimedia
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Uncomment the following line to make your code fail to compile if you use deprecated APIs.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/Time.cpp \
        src/aabb.cpp \
        src/base_scene.cpp \
        src/bow.cpp \
        src/camera.cpp \
        src/cutscene.cpp \
        src/door.cpp \
        src/dqmath.cpp \
        src/entity.cpp \
        src/entity_ai.cpp \
        src/event_logger.cpp \
        src/game_difficulty.cpp \
        src/game_header.cpp \
        src/game_state.cpp \
        src/hit_circle.cpp \
        src/hotbar.cpp \
        src/interactive.cpp \
        src/inventory.cpp \
        src/item.cpp \
        src/keyboard.cpp \
        src/main.cpp \
        src/game_engine.cpp \
        src/melee.cpp \
        src/monster.cpp \
        src/mouse.cpp \
        src/object.cpp \
        src/physical.cpp \
        src/player.cpp \
        src/projectile.cpp \
        src/quest.cpp \
        src/ranged.cpp \
        src/ray.cpp \
        src/scene0.cpp \
        src/scene1.cpp \
        src/scene2.cpp \
        src/scene3.cpp \
        src/scene4.cpp \
        src/scene5.cpp \
        src/testpoint.cpp \
        src/textbox.cpp \
        src/tile.cpp \
        src/tilechoice.cpp \
        src/tilegenerator.cpp \
        src/weapon.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH += /opt/Qt5.8.0/5.8/gcc_64/qml/QtGraphicalEffects
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/aabb.h \
    src/base_scene.h \
    src/bow.h \
    src/door.h \
    src/dqmath.h \
    src/entity.h \
    src/entity_actions.h \
    src/entity_ai.h \
    src/event_logger.h \
    src/game_difficulty.h \
    src/hit_circle.h \
    src/hotbar.h \
    src/interactive.h \
    src/inventory.h \
    src/item.h \
    src/keyboard.h \
    src/main_event.h \
    src/Time.h \
    src/camera.h \
    src/cutscene.h \
    src/game_engine.h \
    src/game_header.h \
    src/game_state.h \
    src/melee.h \
    src/monster.h \
    src/mouse.h \
    src/object.h \
    src/physical.h \
    src/player.h \
    src/projectile.h \
    src/quest.h \
    src/ranged.h \
    src/ray.h \
    src/scene0.h \
    src/scene1.h \
    src/scene2.h \
    src/scene3.h \
    src/scene4.h \
    src/scene5.h \
    src/testpoint.h \
    src/textbox.h \
    src/tile.h \
    src/tilechoice.h \
    src/tilegenerator.h \
    src/vectors.h \
    src/weapon.h

# V PŘÍPADĚ PŘIDÁNÍ NOVÝÁCH SLOŽEK/SOUBORŮ MUSÍ BÝT AKTUALIZOVÁNY : add existing file/folder pravým klikem na projektu
# pokud se nějaké specifické nezobrazuje je to z důvodu mezery ve jméně všechny mezery musí být nahrazeny _ poté bude viditelné

DISTFILES +=






