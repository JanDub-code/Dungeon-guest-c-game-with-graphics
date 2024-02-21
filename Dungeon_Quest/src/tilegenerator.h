#ifndef TILEGENERATOR_H
#define TILEGENERATOR_H

#include <QObject>
#include <QVariant>
#include "tile.h"
#include "camera.h"
#include "game_header.h"
#include "tilechoice.h"

class tileGenerator: public QObject{
    Q_OBJECT
    Q_PROPERTY(QVariant tiles READ getTiles NOTIFY tileCacheChanged) // INFO: Concept
    //Q_PROPERTY(QVariant tiles1 READ getTiles1 CONSTANT)
    Q_PROPERTY(float level_origin_x READ getLevelCameraOriginX NOTIFY cameraPosOrLevelOriginChanged)
    Q_PROPERTY(float level_origin_y READ getLevelCameraOriginY NOTIFY cameraPosOrLevelOriginChanged)
    Q_PROPERTY(int level_w READ QMLgetMapWidth NOTIFY levelDimensionsChanged)
    Q_PROPERTY(int level_h READ QMLgetMapHeight NOTIFY levelDimensionsChanged)


private:
    std::vector<Tile*> m_tiles;
    std::vector<Tile*> m_tiles1;
    std::vector<Tile*> m_tiles2;
    std::vector<Tile*> m_tiles3;
    std::vector<Tile*> m_tiles4;
    std::vector<Tile*> m_tiles5;

    Vec2i m_map_size; // INFO: Concept
    Vec2i m_map_size1; // INFO: Concept
    Vec2i m_map_size2;
    Vec2i m_map_size3;
    Vec2i m_map_size4;
    Vec2i m_map_size5;

    std::vector<Tile*> m_tiles_cache; // INFO: Concept
    Vec2i m_map_size_cache;
    Vec2f m_level_origin;
    tileChoice tilechoice;
public:
    explicit tileGenerator(QObject *parent = nullptr);
    QVariant getTiles() const;
    //QVariant getTiles1() const;
    Q_INVOKABLE QVariant getTilesQML() const;
    //Q_INVOKABLE QVariant getTilesQML1() const;
    void reloadMaps();

private:
    void tileAligner(std::vector<Tile*> &tiles, int w, int h);
    void clearTiles(std::vector<Tile*> tiles); // INFO: Concept
    void setMapSizeCache(const Vec2i size);

    inline int getLevelCameraOriginX() // float to int for QML
    { return int(std::floor((m_level_origin.x/* + 7.0F*/ - Camera::getPos().x) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_W_HALF; }
    inline int getLevelCameraOriginY() // float to int for QML
    { return int(std::floor((m_level_origin.y/* + 8.0F*/ - Camera::getPos().y) * gh::GH_DEFAULT_TILE_VISUAL_SIZE_F)) + gh::GH_SCREEN_H_HALF; }
    void setLevelOriginBasedCurentMap(const std::vector<Tile*> &tiles);
    int getLevelWidth();
    int getLevelHeight();
public:
    void setMap(int map_id); // INFO: Concept
    std::vector<Tile*> *getCppTiles();
    Vec2i getMapSize(); // INFO: Concept
    inline size_t getMapWidth()
    { return size_t(m_map_size_cache.x); }
    inline size_t getMapHeight()
    { return size_t(m_map_size_cache.y); }
    inline int QMLgetMapWidth()
    { return m_map_size_cache.x; }
    inline int QMLgetMapHeight()
    { return m_map_size_cache.y; }
private:
    void generateMap();
    void generateMap1();
    void generateMap2();
    void generateMap3();
    void generateMap4();
    void generateMap5();
    // INFO: init_x init_y -> multiplier
    //       example: 1, 1 means shift it GH_TILES_INIT_SHIFT_X * 1 and GH_TILES_INIT_SHIFT_Y * 1
    //       0, 0 means no shift but original pos beginig from 0, 0
signals:
    void tileCacheChanged(); // INFO: Concept
    void cameraPosOrLevelOriginChanged();
    void levelDimensionsChanged();
};

#endif // TILEGENERATOR_H


