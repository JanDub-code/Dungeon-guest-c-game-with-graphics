#ifndef __OBJECT__
#define __OBJECT__

#include <QObject>
#include <QVariant>
#include <vector>
#include "vectors.h"
#include "camera.h"
#include "game_header.h"

class Physical;
class Item;

class Object : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float x READ getQMLPosX NOTIFY posChanged)
    Q_PROPERTY(float y READ getQMLPosY NOTIFY posChanged)
    Q_PROPERTY(int x_cr READ getQMLPosCamRelX NOTIFY posChanged)
    Q_PROPERTY(int y_cr READ getQMLPosCamRelY NOTIFY posChanged)
    Q_PROPERTY(QString name READ getQName NOTIFY nameChanged)
    Q_PROPERTY(QString texture READ getTexture NOTIFY textureChanged)
    Q_PROPERTY(int w READ getVisualWidth CONSTANT)
    Q_PROPERTY(int h READ getVisualHeight CONSTANT)
    Q_PROPERTY(QuestStatus quest_status READ getQuestState NOTIFY questStatusChanged)
    Q_PROPERTY(bool visible READ isVisible NOTIFY visibilityChanged)
    Q_PROPERTY(bool in_collision READ debugIsInCollision NOTIFY debugCollisionChanged)
    Q_PROPERTY(QString photo READ getPhoto CONSTANT)
protected:
    Vec2f m_pos;
    std::string m_name;
    QString m_texture;
    bool m_visible;
    //Vec2f m_size;
    Vec2i m_visual_size;
    QString m_photo;
public:
    enum class QuestStatus
    {
        QS_NONE = 0x0, // None or invisible
        QS_AVAILABLE = 0x1, // Quest with no progress and not claimed (possible to create a new quest if not created yet)
        QS_PREPARED = 0x2 // Quest with prepared requirements (to be claimed)
    };
    Q_ENUM(QuestStatus)

    enum ObjOrientation
    {
        OO_UP = 0x0,
        OO_DOWN = 0x01,
        OO_LEFT = 0x02,
        OO_RIGHT = 0x03
    };
    Q_ENUM(ObjOrientation)

    ObjOrientation m_orientation;

    Object(QObject *parent = nullptr);
    virtual ~Object();
    virtual void update();
    virtual void fixedUpdate();
    // If not physical, return nullptr
    virtual inline Physical* asPhysical() { return nullptr; }
    inline const Physical *asPhysical() const { return const_cast<Object*>(this)->asPhysical(); }
    //virtual inline Item* asItem() { return nullptr; }
    //inline const Item* asItem() const { return const_cast<Object*>(this)->asItem(); }
    // update is for fast interactions and input (runs as fast as possible)
    // fixedUpdate is for physics update (runs at fixed speed slower than update and is fixedDeltaTime dependent)
    // TODO: move to Physical only if checking for AsPhysical does not impact performance
    inline Vec2f getPos()
    { return m_pos; }

    float getQMLPosX(); // for QML coord display
    float getQMLPosY(); // for QML coord display

    inline int getQMLPosCamRelX() // float to int for QML
    { return int(std::floor((m_pos.x - Camera::getPos().x) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_W_HALF; }
    inline int getQMLPosCamRelY() // float to int for QML
    { return int(std::floor((m_pos.y - Camera::getPos().y) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_H_HALF; }

    void cameraMoveToObj(Camera *cam);
    void setName(std::string name);
    Q_INVOKABLE void setQName(QString name);
    std::string getName() const;
    void setTexture(std::string texture);
    QString getTexture();
    void setVisible();
    void setInvisible();
    bool isVisible();
    Q_INVOKABLE QString getQName();
    int getVisualWidth();
    int getVisualHeight();

    virtual inline void move(Vec2f dist)
    { m_pos += dist; }
    virtual inline void setPos(Vec2f pos)
    { m_pos = pos; }

    void setQuestState(QuestStatus quest_status);

    Q_INVOKABLE inline QuestStatus getQuestState()
    { return m_quest_status; }

    bool m_debug_in_collision;
    bool debugIsInCollision() { return m_debug_in_collision; }
    void setPhoto(std::string photo);
    QString getPhoto() const;
protected:
    QuestStatus m_quest_status;
signals:
    void posChanged();
    void questStatusChanged();
    void nameChanged();
    void textureChanged();
    void visibilityChanged();
    void debugCollisionChanged();
};

typedef std::vector<Object*> v_objects;

#endif
