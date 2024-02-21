import QtQuick 2.15

Rectangle {
    width: 32
    height: 32

    Image {
        anchors.fill: parent
        source: "assets/grass.png"
        //source:"assets/grass.png"
    }

    property alias tile: tileObject

    Tile {
        id: tileObject
    }


}
