import QtQuick 2.9
import QtMultimedia
import GameState 1.0
import Keyboard 1.0

Item {
    id: worldScene
    Image {
        id: sceneBackground
        source: "images/MainMenuBackground.png"
        anchors.fill: parent
        visible: true
    }

    // World ground and obstacles
    /*
    Repeater {
        z: 1
        model: generator.tiles

        Tile {
            tileIndex: index
        }
    }
    */
    Level {
        id: worldLevel        
        z: 1
    }

/*
    TileGen2{
        x:10
        y:400
        visible:true
        z:1
    }
*/
/*
    Rectangle {
        x:200
        y:200

        visible: true
        width: 800
        height: 600

        Grid {
            id: grid
            columns: 6
            rows: 6
            anchors.centerIn: parent
            columnSpacing: 0
            rowSpacing: 0

            Repeater {
                model: 36
                delegate: TileItem {}
            }
        }
    }
*/
    // World objects
    Repeater {
        model: game_engine.objects
        z:2
        Object {
            objectIndex: index
            z:2
        }
    }

    StatusBar {
        id: testBar
        percentageNum: game_engine.player ? (game_engine.player.health / game_engine.player.health_max * 100) : 0
        width: 256
        height: 32
        x: 10
        y: 10
        z: 3
    }

    Grid {
        id: hotbarGrid
        columns: 10
        rows: 1
        x: Math.floor(game_engine.window_w/2 - 10*15)
        y: Math.floor(game_engine.window_h - 35)
        z: 3

        Repeater {
            model: 10

            Rectangle {
                id: hotbarTile
                width: 30
                height: 30
                border.color: "white"
                color: "transparent"
                border.width: 3
            }
        }
    }
/*
    Loader {
        id: mouseLoader
        onLoaded: {
            console.log("Loader loaded!");
        }
    }
*/
/*
    MediaPlayer {
        id: mediaPlayer
        source: "soundtrack/panic.mp3"
        audioOutput: AudioOutput {}
    }
    */

    QuestArrow {
        id: questArrow
        x: 984
        y: 23
        z: 4
    }

    QuestList {
        id: questList
        z: 5
        visible: m_gamestate.state === GameState.GS_QUEST_LIST
        enabled: m_gamestate.state === GameState.GS_QUEST_LIST
    }

    TextBox {
        id: textBox
        z: 6
        visible: m_gamestate.state === GameState.GS_TEXTBOX_POPUP
        enabled: m_gamestate.state === GameState.GS_TEXTBOX_POPUP
    }

    // TODO: Fix problem with invisible buttons. Sometimes QML won't read button states or something?
    QuestPopup {
        id: questPopup
        z: 7
        isEnabled: m_gamestate.state === GameState.GS_QUEST_POPUP
        visible: m_gamestate.state === GameState.GS_QUEST_POPUP
    }

    // TODO: Inventory here?
    Inventory {
        id: playerInventory
        z: 8
        visible: m_gamestate.state === GameState.GS_INVENTORY
        enabled: m_gamestate.state === GameState.GS_INVENTORY
    }

    StackViewChanger {
        id: statePause
        qmlNameTarget: "PauseMenu.qml"
        gameState: m_gamestate.state
        gameStateCheck: GameState.GS_PAUSE_MENU
    }

    StackViewChanger {
        id: stateOver
        qmlNameTarget: "GameOver.qml"
        gameState: m_gamestate.state
        gameStateCheck: GameState.GS_GAME_OVER
    }
}
