import QtQuick
import GameState 1.0
import Mouse 1.0

Item {
    id: questPopup
    visible: false
    property bool isEnabled: false

    Rectangle {
        id: questRect
        x: Math.floor(game_engine.window_w / 2 - 192)
        y: Math.floor(game_engine.window_h / 2 - 256)
        width: 384
        height: 512
        color: "#F7666666"
        property int questIndex: 0 // TODO: Move this to QuestMini.qml because quest with confirmation will be shown only once... or keep it and show it next to mini with buttons invisible
        visible: parent.visible // If quest has some options otherwise false game_engine.active_quest/new_quest (variable active_quest only if there is possibility for multiple quests)
        enabled: parent.isEnabled


        Rectangle {
            id: titleRect
            width: parent.width
            height: 64
            color: "#F7220000"

            Text {
                id: titleText
                text: game_engine.temp_quest !== null ? game_engine.temp_quest.title : "Default title!"
                color: "#FFFFFF"
                font.pixelSize: 18
                font.bold: true
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: bottomRect
            y: 64
            width: parent.width
            height: 384
            color: "#F7001100"

            Text {
                id: bottomText
                text: questRect.getContextType()
                color: "#FFFFFF"
                font.pixelSize: 18
                font.bold: true
                anchors.centerIn: parent
            }
        }

        Button2 {
            id: bAccept
            x: Math.floor(parent.width / 2 - width - 20)
            y: Math.floor(parent.height - height - 20)
            mouseShiftX: questPopup.x + questRect.x + bAccept.x
            mouseShiftY: questPopup.y + questRect.y + bAccept.y
            textString: "Accept"
            textSize: 10
            width: 100
            height: 25
            functionOnClick: parent.actionAccept
            visible: game_engine.temp_quest !== null ? !game_engine.temp_quest.is_claimed : false
        }

        Button2 {
            id: bDecline
            x: Math.floor(parent.width / 2 + 20)
            y: Math.floor(parent.height - height - 20)
            mouseShiftX: questPopup.x + questRect.x + bDecline.x
            mouseShiftY: questPopup.y + questRect.y + bDecline.y
            textString: "Decline"
            isEnabled: game_engine.temp_quest !== null ? !game_engine.temp_quest.is_main : false
            textSize: 10
            width: 100
            height: 25
            functionOnClick: parent.actionDecline
            visible: game_engine.temp_quest !== null ? !game_engine.temp_quest.is_claimed : false
        }

        Button2 {
            id: bComplete
            x: Math.floor(parent.width / 2 - width / 2)
            y: Math.floor(parent.height - height - 20)
            mouseShiftX: questPopup.x + questRect.x + bComplete.x
            mouseShiftY: questPopup.y + questRect.y + bComplete.y
            textString: "Complete"
            textSize: 10
            width: 100
            height: 25
            functionOnClick: parent.actionComplete
            visible: game_engine.temp_quest !== null ? (game_engine.temp_quest.is_previewed ? false : game_engine.temp_quest.is_prepared) : false
        }

        Button2 {
            id: bClosePreview
            x: Math.floor(parent.width / 2 - width / 2)
            y: Math.floor(parent.height - height - 20)
            mouseShiftX: questPopup.x + questRect.x + bComplete.x
            mouseShiftY: questPopup.y + questRect.y + bComplete.y
            textString: "Close preview"
            textSize: 10
            width: 100
            height: 25
            functionOnClick: parent.closePreview
            visible: game_engine.temp_quest !== null ? game_engine.temp_quest.is_previewed : false
        }

        function actionAccept() {
            // do some action
            m_gamestate.setState(GameState.GS_RUN_SCENE);
            game_engine.claimQuest();
            game_engine.switchCursor();
        }

        function actionDecline() {
            // do some action
            m_gamestate.setState(GameState.GS_RUN_SCENE);
            game_engine.declineQuest();
            game_engine.switchCursor();
        }

        function actionComplete() {
            // do some action
            m_gamestate.setState(GameState.GS_RUN_SCENE);
            game_engine.completeQuest();
            game_engine.switchCursor();
        }

        function getContextType() {
            if(game_engine.temp_quest) {
                if (!game_engine.temp_quest.is_prepared) {
                    return game_engine.temp_quest.context;
                }

                return game_engine.temp_quest.fin_context;
            }

            return "Sample text quest!";
        }

        function closePreview() {
            m_gamestate.setState(GameState.GS_RUN_SCENE);
            game_engine.disableQuestPreview();
            game_engine.switchCursor();
        }
    }
}

// TODO: If clicked on available choice, register choice and change game state

// TODO: Add QuestMini.qml and QuestList.qml containing QuestMini {} objects scrollable
