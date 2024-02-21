import QtQuick

Rectangle {
    id: backgroundBar
    property double percentageNum: 100.0;
    property color backgroundColor: "#000000"
    property color statusColor: "#FF0000"
    x: 0
    y: 0
    width: 32
    height: 128
    color: backgroundColor
    visible: true

    Rectangle {
        id: statusBar
        width: getPercWidth()
        height: backgroundBar.height
        color: backgroundBar.statusColor
        visible: backgroundBar.visible
    }

    function getPercWidth() {
        return parseInt((backgroundBar.width * backgroundBar.percentageNum) / 100.0);
    }
}
