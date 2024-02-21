import QtQuick

// INFO: It can be something like a menu to make it easier...
//       or it can be just a rectangle overlaping scene
//       but that would be harder to handle key events
//       (if inventory visible then change Keys event registering? But that should be from in C++ side
//       also game mechanics like entities should be paused like in pause menu aka disable QTimer in C++ to stop calling runFrame() function)
Item {
    id: playerInventory

    Rectangle {
        id: inventoryTitle
        x: Math.floor(game_engine.window_w / 2 - 520/2)
        y: Math.floor(game_engine.window_h / 2 - 520/2 - 50)
        width: 520
        height: 50
        color: "#FF666666"

        Text {
            id: inventoryText
            z: 1
            text: "Inventory"
            color: "#00FF00"
            font.pixelSize: 30
            font.bold: true
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: inventoryContents
        x: Math.floor(game_engine.window_w / 2 - 520/2)
        y: Math.floor(game_engine.window_h / 2 - 520/2)
        width: 520
        height: 520
        color: "#FF666666"

        Grid {
            columns: 7
            rows: 7
            spacing: (520 - 8*2 - 7*64)/6
            x: 8
            y: 8

            Repeater {
                model: 49

                Rectangle {
                    id: backgroundTile
                    width: 64
                    height: 64
                    color: "black"
                }
            }

        }

        Grid {
            columns: 7
            rows: 7
            spacing: (520 - (8 + 64/2 - 45/2)*2 - 7*45)/6
            x: 8 + 64/2 - 45/2
            y: 8 + 64/2 - 45/2

            Repeater {
                model:  m_inventory.invItems

                InventoryItem {
                    inventoryItemIndex: index
                    z:2
                }
            }

        }
    }
}
