import QtQuick

Item {
    id: textBox

    Rectangle {
        id: bottomTextRect
        color: "#CC000000"
        x: 0
        y: 640
        width: game_engine.window_w
        height: 128

        Text {
            id: bottomText
            text: m_textbox.message
            color: "#FFFFFF"
            font.pixelSize: 20
            font.bold: true
            anchors.centerIn: parent
        }
    }
}
