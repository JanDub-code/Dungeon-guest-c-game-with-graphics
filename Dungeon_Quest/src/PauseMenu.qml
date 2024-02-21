import QtQuick
import GameState 1.0

MenuBase {
    id: pauseMenu
    backgroundImage: "images/MainMenuBackground.png"
    buttonSpacingVertical: 12

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
        textString: "Return"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClickParam: 1
        functionOnClick: pauseMenu.sceneSwitch
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
        textString: "Exit"
        textFont: "Old Standard TT"
        textColorDefault: "#D4AF37"
        textBold: true
        textFontSize: 18
        functionOnClickParam: 2
        functionOnClick: pauseMenu.sceneSwitch
    }


    StackViewChanger {
        qmlNameTarget: "Scene.qml"
        gameState: m_gamestate.state
        gameStateCheck: GameState.GS_RUN_SCENE
    }

    function sceneSwitch(scene_id) {
        switch (scene_id) {
        case 1:
            m_gamestate.setState(GameState.GS_RUN_SCENE);
            break;
        case 2:
            game_engine.reset();
            stackView.pop();
            break;
        default:
            break;
        }
    }
}
