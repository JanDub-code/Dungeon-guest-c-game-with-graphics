//pragma Singleton
import QtQuick
import Mouse 1.0
Rectangle {
    id: mousePointer
    x: posX - widthShift
    y: posY - heightShift
    width: 1
    height: 1
    property int widthShift: 1
    property int heightShift: 1
    color: "transparent"
    property string imagePath: setCursor(m_mouse.cur)
    property int posX: 0
    property int posY: 0

    Image {
        id: cursorImage
        source: imagePath
        anchors.fill: parent
        visible: true
    }

    function setDimensions(w, h, w_c = 0, h_c = 0) {
        mousePointer.width = w;
        mousePointer.height = h;
        mousePointer.widthShift = w_c;
        mousePointer.heightShift = h_c;
    }

    // Has nothing to do with m_mouse.setCursor
    function setCursor(type) {
        var temp_w = 8;
        var temp_h = 11;

        if (typeof(type) !== "number") {
            console.log("Input type for setCursor is not a number!");
            setDimensions(temp_w, temp_h);
            return "assets/cursors/default.png";
        }

        switch (type) {
        case Mouse.C_DEFAULT:
            // TODO: Change size and add image
            setDimensions(temp_w, temp_h);
            return "assets/cursors/default.png";
        case Mouse.C_CROSSHAIR:
            temp_w = 11;
            temp_h = 11;
            setDimensions(temp_w, temp_h, Math.ceil(temp_w / 2), Math.ceil(temp_h / 2));
            return "assets/cursors/crosshair.png";
        case Mouse.C_INTERACTIVE:
            // TODO: Change size and add image
            temp_w = 11;
            temp_h = 11;
            setDimensions(temp_w, temp_h, Math.ceil(temp_w / 2), Math.ceil(temp_h / 2));
            return "assets/cursors/interactive.png";
        default:
            console.log("Unknown cursor type!");
            setDimensions(temp_w, temp_h);
            return "assets/cursors/default.png";
        }
    }

    function setPos(x, y) {
        mousePointer.posX = x
        mousePointer.posY = y
        m_mouse.setX(mousePointer.posX)
        m_mouse.setY(mousePointer.posY)
    }
    /*
    function setPos(source) {
        mousePointer.posX = source.x
        mousePointer.posY = source.y
        m_mouse.setX(mousePointer.posX)
        m_mouse.setY(mousePointer.posY)
    }
    */
}
