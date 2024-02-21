import QtQuick
import Mouse 1.0

Item {
    id: questLit

    Rectangle {
        id: listContents
        width: 192
        height: 512
        x: game_engine.window_w - width
        y: 128
        color: "#F7666666"
        border.width: 2
        border.color: "black"
        property int questHeight: 64
        property int gridScroll: 0
        //containmentMask: gridContent
        clip: true

        Rectangle {
            id: listHead
            width: parent.width
            height: 32
            color: "#F7000000"
            z: 2

            Text {
                id: headerText
                text: "Quests"
                color: "#FFFFFF"
                font.pixelSize: 18
                font.bold: true
                anchors.centerIn: parent
            }
        }

        Column {
            id: gridContent
            spacing: 0
            x: listContents.border.width
            y: listContents.gridScroll + listHead.height
            z: 1
            clip: true
            //containmentMask: questsRepeater

            Repeater {
                id: questsRepeater
                model: game_engine.quests

                QuestMini {
                    questIndex: index
                    width: listContents.width - listContents.border.width * 2
                    height: listContents.questHeight - listContents.border.width * 2
                    mouseShiftX: listContents.x + gridContent.x
                    mouseShiftY: listContents.y + gridContent.y
                }
            }
        }

        MouseArea {
            id: scrollableArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.BlankCursor
            onPositionChanged: mouse => {
                mousePointer.setPos(listContents.x + mouse.x, listContents.y + mouse.y);
            }
            onWheel: wheel => {
                console.log("Scrolled: ", wheel.angleDelta.y);
                if (wheel.angleDelta.y > 0) {
                    console.log("Scrolled up!");
                    listContents.scrollGrid(8);
                }
                else {
                    console.log("Scrolled down!");
                    listContents.scrollGrid(-8);
                }
            }
            // TODO: Fix if containmentMask: is not defined then onEntered and onExited won't work
            onEntered: {
                m_mouse.setCursor(Mouse.C_DEFAULT);
            }
            onExited: {
                game_engine.switchCursor();
            }
        }

        function scrollGrid(value) {
            if (value > 0) {
                if ((listContents.gridScroll + value) <= 0) {
                    listContents.gridScroll = listContents.gridScroll + value;
                }
            }
            else {
                var questsClip = (listContents.questHeight * game_engine.quest_count - listContents.height) - Math.abs(value);
                if (listContents.gridScroll > -questsClip) {
                    if ((listContents.gridScroll + value) >= -listContents.questHeight * game_engine.quest_count) {
                        listContents.gridScroll = listContents.gridScroll + value;
                    }
                }
            }
        }
    }
}
