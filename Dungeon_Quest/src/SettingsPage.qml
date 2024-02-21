import QtQuick
// TODO: Consider using MenuBase instead of Rectangle (DRY)
Rectangle {
    id: settingsMenu
    property alias backgroundImage: settingsMenuuBackground.source
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

    Image {
        id: settingsMenuuBackground
        source: ""
        anchors.fill: parent
        visible: !button1.isPressed
    }

    Rectangle {
        id: settingsMenuTitle
        x: game_engine.window_w / 2 - 250
        y: 32
        width: 512
        height: 256

        Image {
            id: settingsMenuImage
            source: "images/MainMenuTitle.png"
            anchors.fill: parent
            visible: true
        }
    }
    function gameQuit() {
        game_engine.reset(); // TODO: Remove after Pause Menu is implemented
        Qt.quit();
    }

    function returnF() {
        stackView.pop()
    }

    Button2 {
        id: button1
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical
        textString: "Back"
        functionOnClick: settingsMenu.returnF

    }



    Button2 {
        id: settingsMenuBtnExit
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical) * 4
        textString: "Quit"
        imagePathDefault: "images/button_test_default.png"
        imagePathHover: "images/button_test_hover.png"
        imagePathPressed: "images/button_test_click.png"
        textColorDefault: "#000000"
        functionOnClick: settingsMenu.gameQuit
        //onClick: Qt.callLater(Qt.quit)
    }


}
