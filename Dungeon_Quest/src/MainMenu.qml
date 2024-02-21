import QtQuick
import Keyboard 1.0
import GameState 1.0

// Using MenuBase because you know... DRY!
MenuBase {
    id: mainMenu
    backgroundImage: "images/MainMenuBackground.png"
    buttonSpacingVertical: 12

    Rectangle {
        id: mainMenuTitle
        x: game_engine.window_w / 2 - 250
        y: 32
        width: 512
        height: 256

        Image {
            id: mainMenuImage
            source: "images/MainMenuTitle.png"
            anchors.fill: parent
            visible: true
        }
    }
    // Buttons
    Button2 {
        id: button
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "New Game"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClickParam: 1
        functionOnClick: mainMenu.sceneSwitch
    }

    Button2 {
        id: button1
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical)
        isEnabled: false
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Continue"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClick: mainMenu.functionNoParam
    }

    Button2 {
        id: button2
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical) * 2
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Load Game"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClick: mainMenu.functionNoParam
    }


    Button2 {
        id: button3
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical) * 3
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Settings"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClickParam: 3
        functionOnClick: mainMenu.sceneSwitch
    }


    Button2 {
        id: button4
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical) * 4
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Credits"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClickParam: 4
        functionOnClick: mainMenu.sceneSwitch
    }


    Button2 {
        id: button5
        x: game_engine.window_w / 2 - buttonShiftHorizontal
        y: buttonShiftVertical + (buttonHeight + buttonSpacingVertical) * 5
        width: 200
        height: 50
        colorDefault: "#001F3F"
        borderColor: "#555"
        borderWidth: 2
        cornersRadius: 8
        textString: "Quit"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClick: mainMenu.gameQuit
    }

        //onClick: Qt.callLater(Qt.quit)


    //signal run(int val)

    // Functions
    function gameQuit()
    {
        game_engine.reset(); // TODO: Remove after Pause Menu is implemented
        Qt.quit();
    }

    function sceneSwitch(scene_id)
    {
        switch (scene_id) {
        case 1: // Start
            game_engine.reset(); // TODO: Add pause menu to avoid using reset here
            game_engine.setup();
            // DEBUG
            stackView.push("Scene.qml");
            break
        case 2: // Load Game
            break
        case 3: // Settings
            m_gamestate.setState(GameState.GS_SETTINGS_MENU);
            // push settings menu
            break
        case 4: // Credits
            stackView.push("Credits.qml");
            break
        default:
            console.log("FATAL ERROR: Unknown scene " + scene_id + "!")
            m_gamestate.setState(GameState.GS_MAIN_MENU);
            // TODO: Reset everything (or just fix this issue permanently)
            game_engine.reset();
            //Qt.quit()
        }
    }

    // DEBUG
    function functionNoParam() {
        console.log("Function with no parameters test succeded!")
    }
}







