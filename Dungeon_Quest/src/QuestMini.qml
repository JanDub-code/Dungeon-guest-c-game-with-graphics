import QtQuick
import Mouse 1.0
import GameState 1.0

Rectangle {
    id: questMini
    property int questIndex: 0
    color: "#F7444444"
    border.width: 1
    border.color: "black"
    property int mouseShiftX: x
    property int mouseShiftY: y

    Rectangle {
        id: thumbnailRect
        x: parent.border.width
        y: parent.border.width
        z: 0
        width: parent.height - parent.border.width * 2
        height: parent.height - parent.border.width * 2
        color: "#F700FF00"
    }

    MouseArea {
        id: questArea
        z: 0
        anchors.fill: parent
        cursorShape: Qt.BlankCursor
        onPositionChanged: mouse => {
            mousePointer.setPos(listContents.x + mouse.x, listContents.y + listHead.height + mouse.y);
        }
        onPressed: {
            questMini.showQuest();
            console.log("Pressed quest in list!");
        }
        onClicked: {
            console.log("Clicked on quest in list!");
        }
    }

    Rectangle {
        id: rightRect
        x: thumbnailRect.width + parent.border.width
        y: parent.border.width
        z: 0
        width: parent.width - parent.border.width * 2 - thumbnailRect.width
        height: parent.height - parent.border.width * 2
        color: "#F7444444"

        Rectangle {
            id: titleRect
            z: 1
            width: parent.width
            height: parent.height / 2 + parent.height / 8
            color: parent.color
            Text {
                id: titleText
                z: 2
                //text: "Sample title!" // m_quest.context
                text: game_engine.quests[questIndex].title
                color: "#FFFFFF"
                font.pixelSize: 10
                font.bold: true
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: buttonsRect
            y: titleRect.height
            z: 1
            width: parent.width
            height: parent.height / 2 - parent.height / 8

            Button2 {
                id: butTrack
                x: parent.width / 2 - width / 2 - width + 10
                y: parent.height / 2 - height / 2
                z: 2
                mouseShiftX: questMini.x + rightRect.x + buttonsRect.x + x + questMini.mouseShiftX
                mouseShiftY: questMini.y + rightRect.y + buttonsRect.y + y + questMini.mouseShiftY
                textString: "Track"
                textSize: 10
                width: parent.width / 4 + 10
                height: parent.height / 2 + parent.height / 4
                isEnabled: !game_engine.quests[questIndex].is_active
                functionOnClick: questMini.setAsActive
            }

            Button2 {
                id: butNoTrack
                x: parent.width / 2 - width / 2 + width - 10
                y: parent.height / 2 - height / 2
                z: 2
                mouseShiftX: questMini.x + rightRect.x + buttonsRect.x + x + questMini.mouseShiftX
                mouseShiftY: questMini.y + rightRect.y + buttonsRect.y + y + questMini.mouseShiftY
                textString: "Stop Tracking"
                textSize: 10
                width: parent.width / 4 + 14
                height: parent.height / 2 + parent.height / 4
                isEnabled: game_engine.quests[questIndex].is_active
                functionOnClick: questMini.setAsInactive
            }
        }
    }

    function showQuest() {
        // TODO: C++ if claimed then allow to exit using escape or add close button
        game_engine.disableQuestPreviews();
        game_engine.enableQuestPreview(questIndex);
        m_gamestate.setState(GameState.GS_QUEST_POPUP);
        m_mouse.setCursor(Mouse.C_DEFAULT);
    }

    function setAsActive() {
        game_engine.setActiveQuest(questMini.questIndex);
    }

    function setAsInactive() {
        game_engine.disableActiveQuest();
    }
}
