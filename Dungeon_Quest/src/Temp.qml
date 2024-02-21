import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.13
import QtQuick.Window 2.2
/*
Window {
    visible: true
    width: 640
    height: 480
    title: "Hra lode"

    Component {
        id: button
        Rectangle {
            property alias text: buttonText.text
            id: buttonBackground
            color: "pink"
            x: 10
            y: 10
            width: 200
            height: 60
            Text {
            id: buttonText
            text: "Ahoj!"
            color: "lightgreen"
            font.bold: true
            font.pixelSize: 30
            //x: 100
            //y: 100
            anchors.centerIn: parent
            //anchors {
                //right: parent.left
                //right: parent.right
                //top: parent.top
                //rightMargin: 20// + parent.width / 2
                //topMargin: 20
                //centerIn: parent
            //}
            RotationAnimator on rotation {
            running: true
            loops: Animation.Infinite
            from: 0
            to: 360
            duration: 1500
        }
            }
            states: [
                State {
                    name:"pressed"
                    PropertyChanges {
                        target: buttonBackground
                        color: "blue"
                     }
                },
                State {
                    name:"hover"
                    PropertyChanges {
                        target: buttonBackground
                        color: "orange"
                     }
                }
            ]
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked:
                    if (buttonBackground.state != "pressed") {
                        buttonBackground.state = "pressed"
                    }
                    else {
                        buttonBackground.state = "hover"
                    }
                onEntered:
                    if (buttonBackground.state != "pressed") {
                        buttonBackground.state = "hover"
                    }
                onExited:
                    if (buttonBackground.state != "pressed") {
                        buttonBackground.state = ""
                    }
            }
        }
    }
    Loader {
        sourceComponent: button
        y: 50
        onLoaded: {
            item.text = "hello"
            item.state = "hover"
            //item.color = "white"
        }
    }
    Loader {
        sourceComponent: button
        y: 150
    }
    Loader {
        sourceComponent: button
        y: 250
    }







    Component {
        id: gButton
        Rectangle {
            id: gButtonBackground
            x: 0
            y: 0
            width: 100
            height: 50
            color: "brown"
            states: [
                State {
                    name:"pressed"
                    PropertyChanges {
                        target: gButtonBackground
                        color: "black"
                     }
                    PropertyChanges {
                        target: gButtonText
                        color: "blue"
                     }
                },
                State {
                    name:"hover"
                    PropertyChanges {
                        target: gButtonBackground
                        color: "lightbrown"
                     }
                    PropertyChanges {
                        target: gButtonText
                        color: "yellow"
                     }
                }
            ]
            Text {
                id: gButtonText
                text: "Button"
                color: "lightgreen"
                font.bold: true
                font.pixelSize: 30
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onPressed:
                    gButtonBackground.state = "pressed"
                onReleased:
                    gButtonBackground.state = "hover"
                onEntered:
                    if (gButtonBackground.state != "pressed") {
                        gButtonBackground.state = "hover"
                    }
                onExited:
                    if (gButtonBackground.state != "pressed") {
                        gButtonBackground.state = ""
                    }
            }
        }
    }
    Component {
        id: tile
        Rectangle {
            id: tileBackground
            x: 200
            y: 200
            width: 48
            height: 48
            color: "black"
            states: [
                State {
                    name:"pressed"
                    PropertyChanges {
                        target: tileBackground
                        color: "red"
                     }
                },
                State {
                    name:"hover"
                    PropertyChanges {
                        target: tileBackground
                        color: "gray"
                     }
                }
            ]
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked:
                    if (tileBackground.state != "pressed") {
                        tileBackground.state = "pressed"
                    }
                    else {
                        tileBackground.state = "hover"
                    }
                onEntered:
                    if (tileBackground.state != "pressed") {
                        tileBackground.state = "hover"
                    }
                onExited:
                    if (tileBackground.state != "pressed") {
                        tileBackground.state = ""
                    }
            }
        }
    }
    Loader {
        sourceComponent: gButton
        x: 150
    }
    // tiles
    Loader {
        sourceComponent: tile
        x: 150
    }
    Loader {
        sourceComponent: tile
        x: 200
    }
    Loader {
        sourceComponent: tile
        x: 250
    }
    Loader {
        sourceComponent: tile
        x: 150
        y: 50
    }
    Loader {
        sourceComponent: tile
        x: 200
        y: 50
    }
    Loader {
        sourceComponent: tile
        x: 250
        y: 50
    }
    Loader {
        sourceComponent: tile
        x: 150
        y: 100
    }
    Loader {
        sourceComponent: tile
        x: 200
        y: 100
    }
    Loader {
        sourceComponent: tile
        x: 250
        y: 100
    }
}
*/
Item {

}
