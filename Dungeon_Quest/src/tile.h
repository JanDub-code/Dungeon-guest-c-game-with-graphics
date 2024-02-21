#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QString>
#include "vectors.h"
#include "aabb.h"
#include "game_header.h"
#include "camera.h"

//#define TILE_SELF_RENDER

class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString photo READ getPhoto CONSTANT)
    Q_PROPERTY(bool untouchable READ isTouchable CONSTANT)
    Q_PROPERTY(int x_cr READ getQMLPosCamRelX NOTIFY camPosChanged)
    Q_PROPERTY(int y_cr READ getQMLPosCamRelY NOTIFY camPosChanged)
    Q_PROPERTY(int z READ getZHeight NOTIFY zHeightChanged)
    Q_PROPERTY(bool in_collision READ debugIsInCollision NOTIFY debugCollisionChanged)
    Q_PROPERTY(bool is_clicked READ debugIsClicked NOTIFY debugCollisionChanged)

public:

    explicit Tile(QObject *parent = nullptr);
    Tile(const QString &photo, bool untouchable = true, int z = 0);
    Tile(const std::pair<QString, bool> &tileInfo);
    //Tile(const QString &photo,bool walkable);
    QString getPhoto() const;
    bool isTouchable() const;
    inline int getQMLPosCamRelX() // float to int for QML
    { return int(std::floor((m_pos.x - Camera::getPos().x) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_W_HALF; }
    inline int getQMLPosCamRelY() // float to int for QML
    { return int(std::floor((m_pos.y - Camera::getPos().y) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_H_HALF; }
    void setZHeight(int z);
    inline int getZHeight()
    { return m_z; }
    bool debugIsInCollision() { return m_debug_in_collision; }
    bool debugIsClicked() { return m_debug_is_clicked; }


    // be careful using this position setter because if position gets changed, object position in vector of tiles should be changed too (std::swap)
    // this is not a chunk-based engine. In a chunk-based engine, tiles or 3D voxels coordinates are based on a position in vector of tiles. Something like:
    // tile = m_world.getChunk(int(floor(desired_pos) / chunk_size)).getTile(int(floor(desired_pos) % chunk_size))
    inline void setPos(Vec2f pos)
    {
        m_pos = pos;
        m_aabb.setPos(pos);
    }

    inline void move(Vec2f pos)
    {
        m_pos += pos;
        m_aabb.move(pos);
    }

    Vec2f m_pos;
    Vec2i m_visual_size;
    AABB m_aabb;
    bool m_debug_in_collision = false;
    bool m_debug_is_clicked = false;
private:
    bool m_untouchable;
    QString m_photo;
    int m_z;
    static const std::map<std::string, int> aabb_img_dbs;

    AABB getAabbBasedOnImageDatabase(const QString &photo);

signals:
    void camPosChanged(); // TODO: Consider removing if tile positionm will be always constant (Change NOTIFY to CONSTANT)
    void debugCollisionChanged();
    void debugClickedChanged();
    void zHeightChanged();

};

#endif // TILE_H
