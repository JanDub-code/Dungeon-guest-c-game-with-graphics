import QtQuick

// Menu "template" for other menus
Rectangle {
    id: menuBase
    property alias backgroundImage: menuBackground.source
    property int buttonShiftVertical: 320
    property int buttonSpacingVertical: 24
    property int buttonWidth: 200
    property int buttonHeight: 50
    property int buttonShiftHorizontal: buttonWidth / 2
    x: 0
    y: 0
    width: game_engine.window_w
    height: game_engine.window_h
    color: "#000000"
    focus: true

    Image {
        id: menuBackground
        source: ""
        anchors.fill: parent
        visible: true
    }
}
