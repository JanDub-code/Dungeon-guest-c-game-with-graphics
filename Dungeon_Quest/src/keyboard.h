#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QObject>

// Singleton
class Keyboard : public QObject
{
    Q_OBJECT
private:
    static const int m_key_count = 256;
    static bool m_keys[m_key_count];
    static bool m_previous[m_key_count];
    static Keyboard *m_instance;

    Keyboard();
    ~Keyboard();
public:
    enum class KKeys
    {
        K_FIRST = 0x0, // int 0
        //K_LBUTTON = 0x01,
        //K_RBUTTON = 0x02,
        //K_MBUTTON = 0x04,
        K_RETURN = 0x0D,
        K_ESCAPE = 0x1B,
        K_SPACE = 0x20,
        K_LEFT = 0x25,
        K_UP = 0x26,
        K_RIGHT = 0x27,
        K_DOWN = 0x28,
        K_0 = 0x30,
        K_9 = 0x39,
        K_A = 0x41,
        K_D = 0x44,
        K_E = 0x45,
        K_I = 0x49,
        K_K = 0x4B,
        K_P = 0x50,
        K_Q = 0x51,
        K_R = 0x52,
        K_S = 0x53,
        K_T = 0x54,
        K_W = 0x57,
        K_Z = 0x5A,
        K_NUM0 = 0x60,
        K_NUM1 = 0x61,
        K_NUM2 = 0x62,
        K_NUM3 = 0x63,
        K_NUM4 = 0x64,
        K_NUM5 = 0x65,
        K_NUM6 = 0x66,
        K_NUM7 = 0x67,
        K_NUM8 = 0x68,
        K_NUM9 = 0x69,
        K_ADD = 0x6B,
        K_SUBTR = 0x6D,
        K_LCONTROL = 0xA3,
        K_LALT = 0xA4,
        K_LAST = 0xFF // int 255
    };
    Q_ENUM(KKeys)

    Q_INVOKABLE static void releaseAll();
    Q_INVOKABLE static void setPressed(KKeys key);
    Q_INVOKABLE static void setReleased(KKeys key);
    Q_INVOKABLE static bool isPressed(KKeys key);
    static bool isClicked(KKeys key);
    static void instantiate();
    static void destroy();
    static Keyboard *getInstance();

};

#endif // KEYBOARD_H

// TODO: make QML access key variables
