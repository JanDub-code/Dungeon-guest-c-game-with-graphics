import QtQuick 2.15
import Camera 1.0
import ObjQuestStatus 1.0

// Object template
Rectangle {
    id: object
    color: "transparent"
    width: game_engine.objects[objectIndex].w
    height: game_engine.objects[objectIndex].h
    // INFO: It is a bad idea to do calculations here since QML is running fast
    x: game_engine.objects[objectIndex].x_cr//Math.floor((game_engine.objects[objectIndex].x - m_maincam.x) / TILE_SIZE + (game_engine.window_w / 2))// - (object.width / 2)
    y: game_engine.objects[objectIndex].y_cr//Math.floor((game_engine.objects[objectIndex].y - m_maincam.y) / TILE_SIZE + (game_engine.window_h / 2))// - (object.height / 2)
    property int objectIndex: 0
    //property alias objectImage: backgroundImage.source
    property var objectImage;
    //property alias imageVisibility: backgroundImage.visible
    property bool debugInfoVisible: false
    visible: game_engine.objects[objectIndex].visible

    Image {
        id: backgroundImage
        anchors.fill: parent      
        source: getImageSrc()
        visible: true
    }

    // DEBUG
    Text {
        id: objName
        font.pixelSize: 8
        text: game_engine.objects[objectIndex].name
        y: -34
        visible: debugInfoVisible
    }

    Text {
        id: coordX
        font.pixelSize: 8
        text: "X: " + game_engine.objects[objectIndex].x
        y: -25
        visible: debugInfoVisible
    }

    Text {
        id: coordY
        font.pixelSize: 8
        text: "Y: " + game_engine.objects[objectIndex].y
        y: -16
        visible: debugInfoVisible
    }

    Image {
        id: questStatus
        x: Math.floor(object.width / 2) - 7
        y: -(21 + 10)
        source: getQuestImg()
        visible: game_engine.objects[objectIndex].quest_status !== ObjQuestStatus.QS_NONE
    }

    Rectangle {
        id: debugCollider
        anchors.fill: parent
        color: "#FF0077"
        visible: game_engine.objects[objectIndex].in_collision
    }

    function getImageSrc() {
        var imagePath = game_engine.objects[objectIndex].texture;
        if (imagePath !== "") {
            return imagePath;
        }
        else {
            return "assets/undefined.png";
        }
    }

    function getQuestImg() {
        switch (game_engine.objects[objectIndex].quest_status) {
        case ObjQuestStatus.QS_AVAILABLE:
            return "assets/quest_states/quest_available.png";
        case ObjQuestStatus.QS_PREPARED:
            return "assets/quest_states/quest_complete.png";
        default:
            return "";
        }
    }
}
