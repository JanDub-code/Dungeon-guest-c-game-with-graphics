import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
//import SVC 1.0
import GameState 1.0

Window {
    id: root
    width: game_engine.window_w//Style.mainWindowWidth
    height: game_engine.window_h//Style.mainWindowHeight
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height
    visible: true
    title: "Dungeon Quest 1"


    property Loader loader


    StackView {
        id: stackView
        anchors.fill: parent
        focus: true

            // První scéna (menu)

            // Počáteční scéna
        initialItem: Loader {
            id: pageLoader
            source: "MainMenu.qml"
            onLoaded: {
                loader = pageLoader; // Assign the loader to the property
                //game_engine.setup()
            }
        }

        KeyboardInput {
            id: kbd
        }

        Keys.onPressed: event => {
            kbd.keyEvents(event, m_keyboard.setPressed)
        }
        Keys.onReleased: event => {
            kbd.keyEvents(event, m_keyboard.setReleased)
        }

        MousePointer {
            id: mousePointer
            z: 7
            // TODO: need help with drawing over buttons
        }

        MouseInput {
            id: mou
        }

        MouseArea {
            id: mainMouseArea
            anchors.fill: parent //worldScene
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons
            cursorShape: Qt.BlankCursor
            onPositionChanged: mouse => {
                mousePointer.setPos(mouse.x, mouse.y);
            }
            onPressed: mouse => {
                mou.mouseEvents(mouse, m_mouse.setPressed)
            }
            onReleased: mouse => {
                mou.mouseEvents(mouse, m_mouse.setReleased)
            }
            onEntered:
            {
                //mousePointer.visible = true
            }
            onExited:
            {
                //mousePointer.visible = false
            }
        }
    }
}
