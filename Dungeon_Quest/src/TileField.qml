import QtQuick

Rectangle {


    width:400
    height:400

    Grid {
        anchors.centerIn: parent
        columns: 7
        rows: 7
        spacing: 0

        Repeater {
            model: generator.tiles

            Tile {
                tileIndex: index
            }
        }
    }
}

