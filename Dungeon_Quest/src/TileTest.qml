import QtQuick


Rectangle {
    width: 50
    height: 50

    Text {
        id: name
        anchors.centerIn: parent
        text: "Text na indexu 7: " + (generator.getTilesQML().length > 7 ? generator.getTilesQML()[7].photo : "N/A")
    }

    Component.onCompleted: {
        console.log("Délka pole tiles:", generator.getTilesQML().length);
        console.log("Obsah pole tiles:", generator.getTilesQML());
    }
}
