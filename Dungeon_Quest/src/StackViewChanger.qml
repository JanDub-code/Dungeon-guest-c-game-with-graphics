//pragma Singleton
import QtQuick
import GameState 1.0

QtObject {
    id: stackViewChanger
    property string qmlNameTarget: undefined
    property int gameState: undefined
    property int gameStateCheck: undefined

    onGameStateChanged: {
        console.log("onGameStateChanged");
        changeView();
    }

    function changeView() {
        if (gameState === gameStateCheck) {
            console.log("Game state match. CHANGING STACKVIEW!", gameState)
            stackView.pop();
            stackView.push(qmlNameTarget)
        }
    }
}
