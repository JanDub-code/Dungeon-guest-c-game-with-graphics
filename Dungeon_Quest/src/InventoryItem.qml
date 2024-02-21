import QtQuick

Rectangle {
    property string imageSource:  !!m_inventory.invItems[inventoryItemIndex] ? "assets/Equipment_Player/" + m_inventory.invItems[inventoryItemIndex].photo : ""
    property int inventoryItemIndex: 0

    id : inventoryItem
    width: 45
    height: 45
    color: "black"

    Image {

        source: imageSource
        anchors.fill: parent
        visible: !!m_inventory.invItems[inventoryItemIndex]

    }


}
