#ifndef MOUSE_H
#define MOUSE_H

#include <QObject>
#include "vectors.h"

class Mouse : public QObject
{
    Q_OBJECT
    //Q_ENUMS(MButtons)
    Q_PROPERTY(MCursors cur READ getCursor NOTIFY mouseCursorChanged)
private:
    static const int m_button_count = 5;
    static bool m_buttons[m_button_count];
    static bool m_previous[m_button_count];
    static Mouse *m_instance;
    static Vec2f m_pos;

    Mouse();
    ~Mouse();
public:
    enum class MButtons
    {
        B_FIRST = 0x0, // int 0
        B_LBUTTON = 0x1,
        B_RBUTTON = 0x2,
        B_MBUTTON = 0x3,
        B_LAST = 0xF
    };
    Q_ENUM(MButtons)

    enum class MCursors
    {
        C_DEFAULT = 0x0, // int 0
        C_CROSSHAIR = 0x1,
        C_INTERACTIVE = 0x2
    };
    Q_ENUM(MCursors)

    Q_INVOKABLE static void releaseAll();
    Q_INVOKABLE static void setPressed(MButtons button);
    Q_INVOKABLE static void setReleased(MButtons button);
    Q_INVOKABLE static bool isPressed(MButtons button);
    static bool isClicked(MButtons button);
    Q_INVOKABLE static void setX(int x);
    Q_INVOKABLE static void setY(int y);
    Q_INVOKABLE static MCursors getCursor();
    Q_INVOKABLE static void setCursor(MCursors cur);
    // INFO: Be aware that m_pos is relative to screen and not to the game coordinates!!!
    static Vec2f getPos();
    static Vec2f getTileTransformedPos();
    static void instantiate();
    static void destroy();
    static Mouse *getInstance();
private:
    static MCursors m_cursor;
signals:
    void mouseCursorChanged();
};
//Q_DECLARE_METATYPE(Mouse::MCursors)

#endif // MOUSE_H
