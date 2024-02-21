import QtQuick
import Mouse 1.0

Item {
    id: mouseInput
    function mouseEvents(mouse, mou_funct)
    {
        if (mouse.button === Qt.LeftButton) {
            mou_funct(Mouse.B_LBUTTON)
        }
        if (mouse.button === Qt.RightButton) {
            mou_funct(Mouse.B_RBUTTON)
        }
        if (mouse.button === Qt.MiddleButton) {
            mou_funct(Mouse.B_MBUTTON)
        }
    }
}
