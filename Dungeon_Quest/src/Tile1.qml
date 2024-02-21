import QtQuick

Item {
    property string imageSource: "assets/" + generator.tiles1[tileIndex].photo
    property int tileIndex: 0
    id : tile1
    width: 32
    height: 32

        Image {
            anchors.fill: parent
            source: imageSource
        }

}
