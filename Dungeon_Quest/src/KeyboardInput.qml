import QtQuick
import Keyboard 1.0

Item {
    id: keyboardInput

    // TODO: Remove everything that is not related to key press passing to C++ side
    function keyEvents(event, kbd_funct)
    {
        if (!event.isAutoRepeat) {
            switch (event.key) {
            case Qt.Key_Escape:
                kbd_funct(Keyboard.K_ESCAPE)
                break
            case Qt.Key_Space:
                kbd_funct(Keyboard.K_SPACE)
            break
            case Qt.Key_Return:
                kbd_funct(Keyboard.K_RETURN)
            break
            case Qt.Key_Control:
                kbd_funct(Keyboard.K_LCONTROL)
            break
            case Qt.Key_Alt:
                kbd_funct(Keyboard.K_LALT)
            break
            case Qt.Key_A:
                kbd_funct(Keyboard.K_A)
                break
            case Qt.Key_D:
                kbd_funct(Keyboard.K_D)
                break
            case Qt.Key_E:
                kbd_funct(Keyboard.K_E)
                break
            case Qt.Key_I:
                kbd_funct(Keyboard.K_I)
                break
            case Qt.Key_K:
                kbd_funct(Keyboard.K_K)
                break
            case Qt.Key_P:
                kbd_funct(Keyboard.K_P)
                break
            case Qt.Key_Q:
                kbd_funct(Keyboard.K_Q)
                break
            case Qt.Key_R:
                kbd_funct(Keyboard.K_R)
                break
            case Qt.Key_S:
                kbd_funct(Keyboard.K_S)
                break
            case Qt.Key_T:
                kbd_funct(Keyboard.K_T)
                break
            case Qt.Key_W:
                kbd_funct(Keyboard.K_W)
                break
            case Qt.Key_Z:
                kbd_funct(Keyboard.K_Z)
                break
            case Qt.Key_0:
                kbd_funct(Keyboard.K_NUM0)
                break
            case Qt.Key_1:
                kbd_funct(Keyboard.K_NUM1)
                break
            case Qt.Key_2:
                kbd_funct(Keyboard.K_NUM2)
                break
            case Qt.Key_3:
                kbd_funct(Keyboard.K_NUM3)
                break
            case Qt.Key_4:
                kbd_funct(Keyboard.K_NUM4)
                break
            case Qt.Key_5:
                kbd_funct(Keyboard.K_NUM5)
                break
            case Qt.Key_6:
                kbd_funct(Keyboard.K_NUM6)
                break
            case Qt.Key_7:
                kbd_funct(Keyboard.K_NUM7)
                break
            case Qt.Key_8:
                kbd_funct(Keyboard.K_NUM8)
                break
            case Qt.Key_9:
                kbd_funct(Keyboard.K_NUM9)
                break
            case Qt.Key_Plus:
                kbd_funct(Keyboard.K_ADD)
                break
            case Qt.Key_Minus:
                kbd_funct(Keyboard.K_SUBTR)
                break
            case Qt.Key_Up:
                kbd_funct(Keyboard.K_UP)
                break
            case Qt.Key_Down:
                kbd_funct(Keyboard.K_DOWN)
                break
            case Qt.Key_Left:
                kbd_funct(Keyboard.K_LEFT)
                break
            case Qt.Key_Right:
                kbd_funct(Keyboard.K_RIGHT)
                break
            default:
            }
        }
    }
}
