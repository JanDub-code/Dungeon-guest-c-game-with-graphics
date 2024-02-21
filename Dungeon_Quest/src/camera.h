#ifndef __CAMERA__
#define __CAMERA__

#include <QObject>
#include "vectors.h"

// This serves for view position (2D viewport)
// INFO: Camera will be only one because we don't want this game too complicated (This is not the only project we students have to work on)
class Camera : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float x READ getPosX NOTIFY posChangedQML)
    Q_PROPERTY(float y READ getPosY NOTIFY posChangedQML)
private:
    //hehehheheheehehehehehhe
    static Vec2f m_pos;
    static int m_width;
    static int m_heihgt;
    static int m_borders_x; // borders LR
    static int m_borders_y; // borders UD
    static bool m_pos_changed;
    static Camera *m_instance;
    // INFO: Borders can be used to crop camera dimensions (use it for example for player camera shifter)
    Camera();
    ~Camera();
public:
    static inline Vec2f getPos()
    { return m_pos; }
    static inline void setPos(const Vec2f &pos)
    { m_pos = pos; }
    static inline void move(const Vec2f &dist)
    { m_pos += dist; }

    static Vec2i getDimensions();
    Q_INVOKABLE int getWidth();
    Q_INVOKABLE int getHeight();
    static void setBorderX(float x);
    static void setBorderY(float y);
    static int getBorderX();
    static int getBorderY();
    Q_INVOKABLE static float getPosX();
    Q_INVOKABLE static float getPosY();
    static void setPosChanged();
    static void resetPosChanged();
    static bool posChanged();

    static void instantiate();
    static void destroy();
    static Camera *getInstance();
signals:
    void posChangedQML();
};

#endif

// HINT: For QML object out of borders detection use camera width and height
