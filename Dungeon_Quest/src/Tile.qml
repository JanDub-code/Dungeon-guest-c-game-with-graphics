import QtQuick 2.15
import Camera 1.0

Item {
    property string imageSource: "assets/" + generator.tiles[tileIndex].photo
    property int tileIndex: 0
    id : tile
    width: TILE_SIZE
    height: TILE_SIZE
    //x: generator.tiles[tileIndex].x_cr//Math.floor((generator.tiles[tileIndex].x - m_maincam.x) / TILE_SIZE + (game_engine.window_w / 2))
    //y: generator.tiles[tileIndex].y_cr//Math.floor((generator.tiles[tileIndex].y - m_maincam.y) / TILE_SIZE + (game_engine.window_h / 2))
    z: generator.tiles[tileIndex].z//generator.tiles[tileIndex].z ? generator.tiles[tileIndex] : parent.z

        Image {
            anchors.fill: parent
            source: imageSource
            //source: "assets/grass.png"
        }

        Rectangle {
            id: debugCollider
            anchors.fill: parent
            color: "#FF0077"
            visible: generator.tiles[tileIndex].in_collision
        }

        Rectangle {
            id: debugClicked
            anchors.fill: parent
            color: "#00FFFF"
            visible: generator.tiles[tileIndex].is_clicked
        }
}



