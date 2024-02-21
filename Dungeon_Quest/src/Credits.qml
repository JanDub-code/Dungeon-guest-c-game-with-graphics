import QtQuick
import GameState 1.0

MenuBase {
    id: creditsPage
    backgroundImage: "images/MainMenuBackground.png"
    buttonSpacingVertical: 12

    Text {
        anchors.centerIn: parent
        text: "This game took a lot of hard teamwork but it was definitely worth it.\nThe game aims to be a classic RPG for pure enjoyment.\nAuthors: Přemysl Křivánek, Jan Dub, Jan Knoth"
        font.pixelSize: 24
        color: "#FFFFFF" // White text
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }

    Button2 {
        id: exitButton
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
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
        functionOnClick: creditsPage.sceneSwitch
    }

    StackViewChanger {
        qmlNameTarget: "Scene.qml"
        gameState: m_gamestate.state
        gameStateCheck: GameState.GS_RUN_SCENE
    }

    function sceneSwitch(scene_id) {
        switch (scene_id) {
        case 2:
            game_engine.reset();
            stackView.pop();
            break;
        default:
            break;
        }
    }
}
