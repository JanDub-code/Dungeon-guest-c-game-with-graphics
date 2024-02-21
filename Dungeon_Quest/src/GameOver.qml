import QtQuick
import GameState 1.0

MenuBase {
    id: pauseMenu
    backgroundImage: "images/MainMenuBackground.png"
    buttonSpacingVertical: 12


    Item {
        id: text


            Text {
                id: bottomText
                text: "You are dead!"
                color: "#FFFFFF"
                font.pixelSize: 20
                font.bold: true
                x: game_engine.window_w/2 - 67
                y: 286
            }
            Text {
                id: bottomT
                text: "Your undoing is now inevitable."
                color: "#FFFFFF"
                font.pixelSize: 20
                font.bold: true
                x: game_engine.window_w/2 - 135
                y: 305
            }

    }

    Button2 {
        id: button1
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical)
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Back to main menu"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClick: pauseMenu.sceneSwitch
    }

    function sceneSwitch(scene_id) {

            game_engine.reset();
            stackView.pop();

    }
}
