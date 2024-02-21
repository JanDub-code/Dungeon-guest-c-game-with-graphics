import QtQuick

// Default button
Rectangle {
    id: button
    property alias textString: buttonText.text;
    property alias textColor: buttonText.color;
    property alias textSize: buttonText.font.pixelSize;
    property alias textBold: buttonText.font.bold;
    property color colorDefault: "#777788";
    property color colorHover: "#7777AA";
    property color colorPressed: "#8888AA";
    property color colorDisabled: "#FF0000";
    property color textColorDefault: "#FFFFFF";
    property color textColorHover: "#FFFF00";
    property color textColorPressed: "#FFFF00";
    property color textColorDisabled: "#000000";
    property string imagePathDefault: "";
    property string imagePathHover: "";
    property string imagePathPressed: "";
    property string imagePathDisabled: "";
    property color borderColor: "#555";
    property int borderWidth: 2;
    property int cornersRadius: 8
    property string textFont: "Arial";
    property int textFontSize: 30
    //property alias onClick: clickableArea.onClicked;
    property bool isHovered: false;
    property bool isPressed: false;
    property bool isEnabled: true;
    property var functionOnClick;
    property var functionOnClickParam; // If undefined, function must have no parameters
    property int mouseShiftX: x;
    property int mouseShiftY: y;
    property string stateDefault: ""
    property string stateDisabled: "disabled"
    property string statePressed: "pressed"
    property string stateHover: "hover"
    enabled: isEnabled
    color: colorDefault
    x: 0
    y: 0
    width: 200
    height: 50
    rotation: 0
    radius: button.cornersRadius
    border.color: button.borderColor
    border.width: button.borderWidth
    state: button.enabled ? button.stateDefault : button.stateDisabled // Init state

    // Optional background
    Image {
        id: buttonImage
        source: imagePathDefault
        anchors.fill: parent
        visible: true
    }

    // Button text
    Text {
        id: buttonText
        text: "Button"
        color: textColorDefault
        font.pixelSize: button.textFontSize
        font.bold: true
        anchors.centerIn: parent
        font.family: button.textFont
    }

    // Button states
    states: [
        State {
            name: button.stateHover
            PropertyChanges {
                target: button
                color: colorHover
             }
            PropertyChanges {
                target: buttonText
                color: textColorHover
             }
            PropertyChanges {
                target: buttonImage
                source: imagePathHover
             }
        },
        State {
            name: button.statePressed
            PropertyChanges {
                target: button
                color: colorPressed
             }
            PropertyChanges {
                target: buttonText
                color: textColorPressed
             }
            PropertyChanges {
                target: buttonImage
                source: imagePathPressed
             }
        },
        State {
            name: button.stateDisabled
            PropertyChanges {
                target: button
                color: colorDisabled
             }
            PropertyChanges {
                target: buttonText
                color: textColorDisabled
             }
            PropertyChanges {
                target: buttonImage
                source: imagePathDisabled
             }
        }
    ]

    // Mouse events
    MouseArea {
        id: clickableArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: button.enabled
        cursorShape: Qt.BlankCursor
        onPositionChanged: mouse => {
            mousePointer.setPos(button.mouseShiftX + mouse.x, button.mouseShiftY + mouse.y);
        }
        // TODO: Need help with mouse pointer not rendering on button area
        onEntered:
        {
            if (button.state !== button.statePressed) {
                button.state = button.stateHover
                button.isHovered = true
            }
        }
        onExited:
        {
            button.state = button.stateDefault
            button.isHovered = false
            button.isPressed = false
            button.isDisabled();
        }
        onPressed:
        if (button.state !== button.statePressed) {
            button.state = button.statePressed
            button.isPressed = true
        }
        onReleased:
        if (button.state === button.statePressed) {
            button.state = button.stateHover
            button.isPressed = false
        }
        onClicked:
        {
            if (typeof(button.functionOnClick) === 'function')
            {
                if (typeof(button.functionOnClickParam) === "undefined") {
                    button.functionOnClick()
                }
                else {
                    button.functionOnClick(button.functionOnClickParam)
                }
            }
        }
    }

    function isDisabled() {
        if (button.isEnabled) {
            console.log("Button enabled!");
            button.state = button.stateDefault;
        }
        else {
            console.log("Button disabled!");
            button.state = button.stateDisabled;
        }
    }
}

// TODO: Fix flashing cursor when entering or exiting button surface
