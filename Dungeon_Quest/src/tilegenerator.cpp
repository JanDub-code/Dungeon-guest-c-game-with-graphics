#include "tilegenerator.h"
#include <QVariant>
#include "dqmath.h"

tileGenerator::tileGenerator(QObject *parent) : QObject(parent)
{
    m_map_size_cache = Vec2i(0);
    reloadMaps();
    m_level_origin = 0.0F;
}

QVariant tileGenerator::getTiles() const {
    return QVariant::fromValue(/*m_tiles*/m_tiles_cache);
}


//QVariant tileGenerator::getTiles1() const {
//    return QVariant::fromValue(m_tiles1);
//}


QVariant tileGenerator::getTilesQML() const {
    return QVariant::fromValue(/*m_tiles*/m_tiles_cache);
}

//QVariant tileGenerator::getTilesQML1() const {
//    return QVariant::fromValue(m_tiles1);
//}

// Put all the map generators here
void tileGenerator::reloadMaps() {
    clearTiles(m_tiles);
    clearTiles(m_tiles1);
    clearTiles(m_tiles2);
    clearTiles(m_tiles3);
    clearTiles(m_tiles4);
    clearTiles(m_tiles5);
    generateMap();
    generateMap1();
    generateMap2();
    generateMap3();
    generateMap4();
    generateMap5();
}
// INFO: Not a voxel game
void tileGenerator::tileAligner(std::vector<Tile *> &tiles, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Vec2f temp_align = Vec2f(float(x), float(y));
            tiles.at(DQMath::xyToVec1(x, y, w))->move(temp_align);
        }
    }
}

// INFO: Concept
void tileGenerator::clearTiles(std::vector<Tile*> tiles)
{
    for (auto tc : tiles)
    {
        delete tc;
    }

    tiles.clear();
}

void tileGenerator::setMapSizeCache(const Vec2i size)
{
    m_map_size_cache = size;
    emit levelDimensionsChanged();
}
#include <iostream>
void tileGenerator::setLevelOriginBasedCurentMap(const std::vector<Tile*> &tiles)
{
    if (tiles.size())
    {
        m_level_origin = tiles[0]->m_pos;
        std::cout << "Origin X: " << m_level_origin.x << "\nOrigin Y: " << m_level_origin.y << std::endl;
        emit cameraPosOrLevelOriginChanged();
        return;
    }

    m_level_origin = 0.0F;
    emit cameraPosOrLevelOriginChanged();
}

int tileGenerator::getLevelWidth()
{
    return m_map_size_cache.x;
}

int tileGenerator::getLevelHeight()
{
    return m_map_size_cache.y;
}

// INFO: Concept
void tileGenerator::setMap(int map_id) {
    m_tiles_cache = {}; // Because of QML complaining about grid being too big for rows and columns
    emit tileCacheChanged();

    switch (map_id) {
    case 0:
        setMapSizeCache(m_map_size);
        m_tiles_cache = m_tiles;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    case 1:
        setMapSizeCache(m_map_size1);
        m_tiles_cache = m_tiles1;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    case 2:
        setMapSizeCache(m_map_size2);
        m_tiles_cache = m_tiles2;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    case 3:
        setMapSizeCache(m_map_size3);
        m_tiles_cache = m_tiles3;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    case 4:
        setMapSizeCache(m_map_size4);
        m_tiles_cache = m_tiles4;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    case 5:
        setMapSizeCache(m_map_size5);
        m_tiles_cache = m_tiles5;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    default:
        setMapSizeCache(m_map_size);
        m_tiles_cache = m_tiles;
        setLevelOriginBasedCurentMap(m_tiles_cache);
        break;
    }

    emit tileCacheChanged();
}

std::vector<Tile*> *tileGenerator::getCppTiles() {
    return &m_tiles_cache; // INFO: Concept
}

// INFO: Concept
Vec2i tileGenerator::getMapSize() {
    return m_map_size_cache;
}

void tileGenerator::generateMap() {
    int grid_w = 14;
    int grid_h = 19;
    // TODO: Maybe implement map dimension checker
    m_map_size = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles); // INFO: Concept
    m_tiles = {
               new Tile("castle_levyvrch.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_nahore.png",false),new Tile("castle_pravohore.png",false),
                new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()), new Tile("grass_slab.png"), new Tile("grass.png"), new Tile("grass_slab.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_flower.png"),new Tile("grass_flower1.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("grass.png"), new Tile("grass.png"), new Tile("grass_flower1.png"),new Tile("barels.png",false),new Tile("grass_flower.png"),new Tile("grass_flower1.png"),new Tile("grass_flower1.png"),new Tile("grass_slab.png"),new Tile(tilechoice.getRandomTile()),new Tile("grass_flower.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()), new Tile("grass_flower.png"), new Tile("box.png",false), new Tile("grass.png"), new Tile("grass_slab.png"),new Tile("grass.png"),new Tile("grass_slab.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_flower.png"),new Tile(tilechoice.getRandomTile()),new Tile("grass_slab.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass.png"), new Tile("grass.png"), new Tile("grass_flower.png"), new Tile("grass.png"), new Tile("grass_flower1.png"),new Tile(tilechoice.getRandomTile()),new Tile("grass_slab1.png"),new Tile("grass.png"),new Tile("box.png",false),new Tile("grass_slab1.png"),new Tile("grass_slab.png"),new Tile("grass.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false), new Tile("grass_slab.png"), new Tile("grass.png"), new Tile("grass.png"), new Tile("grass_flower.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("bones.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("barels.png",false),new Tile("grass.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass.png"), new Tile("grass.png"), new Tile("grass.png"), new Tile("grass_slab1.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_flower1.png"),new Tile("grass.png"),new Tile("grass_flower.png"),new Tile("grass.png"),new Tile(tilechoice.getRandomTile()),new Tile("box.png",false),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass_flower1.png"), new Tile("barels.png",false), new Tile("grass.png"), new Tile("grass_slab.png"), new Tile("grass.png"),new Tile(tilechoice.getRandomTile()),new Tile("grass.png"),new Tile("box.png",false),new Tile("grass.png"),new Tile("grass_slab1.png"),new Tile("grass_flower1.png"),new Tile("grass.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass_slab1.png"), new Tile("grass_slab.png"), new Tile("grass.png"), new Tile("grass_flower1.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_slab.png"),new Tile("grass.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass.png"), new Tile("grass.png"), new Tile("grass.png"), new Tile("grass_slab.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_flower1.png"),new Tile("grass.png"),new Tile(tilechoice.getRandomTile()),new Tile("barels.png",false),new Tile("grass_flower.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass_flower.png"), new Tile("box.png",false), new Tile(tilechoice.getRandomTile()), new Tile("grass_slab.png"), new Tile("grass_slab1.png"),new Tile("grass_flower1.png"),new Tile("barels.png",false),new Tile("grass.png"),new Tile("grass_slab1.png"),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_slab.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("bones.png"), new Tile("grass_flower1.png"), new Tile("grass.png"), new Tile("grass_flower.png"), new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_flower1.png"),new Tile("grass.png"),new Tile("grass_flower1.png"),new Tile("grass_flower.png"),new Tile("grass.png"),new Tile("bones.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png",false),new Tile("grass.png"), new Tile("grass_slab.png"), new Tile("grass.png"), new Tile("grass_slab.png"), new Tile("grass.png"),new Tile("schody000.png",false),new Tile("schody001.png",false),new Tile("grass.png"),new Tile("grass.png"),new Tile("grass_slab.png"),new Tile("grass.png"),new Tile("grass_flower1.png"),new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("schody002.png",false),new Tile("schody003.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_spodniprava.png",false),
               new Tile(),new Tile(),new Tile(),new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile("schody004.png",false),new Tile("schody005.png",false),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile("castle_pravo.png",false),new Tile(),new Tile(),new Tile(),
                new Tile(),new Tile(),new Tile(),new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile("castle_pravo.png",false),new Tile(),new Tile(),new Tile(),
                new Tile(),new Tile(),new Tile(),new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile("castle_pravo.png",false),new Tile(),new Tile(),new Tile(),
                new Tile(),new Tile(),new Tile(),new Tile("castle_levo.png",false),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()),new Tile("castle_pravo.png",false),new Tile(),new Tile(),new Tile(),
                new Tile(),new Tile(),new Tile(),new Tile("castle_levodole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_dole.png",false),new Tile("castle_spodniprava.png",false),new Tile(),new Tile(),new Tile(),
    };
    tileAligner(m_tiles, grid_w, grid_h);
}

void tileGenerator::generateMap1() {
    int grid_w = 18;
    int grid_h = 7;
    // TODO: Maybe implement map dimension checker
    m_map_size1 = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles1); // INFO: Concept
    m_tiles1 = {
                new Tile("castle_levyvrch.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false), new Tile("castle_pravohore.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),               new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),               new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),              new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),     new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),           new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()),               new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false),new Tile("castle_dole.png", false),new Tile("castle_dole.png", false),new Tile("castle_dole.png", false),new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false),new Tile("castle_dole.png", false),new Tile("castle_dole.png", false),new Tile("castle_dole.png", false), new Tile("castle_spodniprava.png", false)

    };
    tileAligner(m_tiles1, grid_w, grid_h);
}


void tileGenerator::generateMap2(){
    int grid_w = 7;
    int grid_h = 18;
    // TODO: Maybe implement map dimension checker
    m_map_size2 = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles2); // INFO: Concept
    m_tiles2 = {
                new Tile("castle_levyvrch.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_pravohore.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_spodniprava.png", false)
    };
    tileAligner(m_tiles2, grid_w, grid_h);

}

void tileGenerator::generateMap3(){
    int grid_w = 7;
    int grid_h = 17;
    // TODO: Maybe implement map dimension checker
    m_map_size3 = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles3); // INFO: Concept
    m_tiles3 = {
                new Tile("castle_levyvrch.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_pravohore.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_spodniprava.png", false)
    };
    tileAligner(m_tiles3, grid_w, grid_h);

}

void tileGenerator::generateMap4(){
    int grid_w = 12;
    int grid_h = 14;
    // TODO: Maybe implement map dimension checker
    m_map_size4 = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles4); // INFO: Concept
    m_tiles4 = {
                new Tile("castle_levyvrch.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false),new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false),  new Tile("castle_pravohore.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()),new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile(tilechoice.getRandomTile()), new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false),new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_spodniprava.png", false)
    };
    tileAligner(m_tiles4, grid_w, grid_h);

}
void tileGenerator::generateMap5(){
    int grid_w = 7;
    int grid_h = 17;
    // TODO: Maybe implement map dimension checker
    m_map_size5 = Vec2i(grid_w, grid_h);
    clearTiles(m_tiles5); // INFO: Concept
    m_tiles5 = {
                new Tile("castle_levyvrch.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_nahore.png", false), new Tile("castle_pravohore.png", false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levo.png", false), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile(tilechoice.getCastle()), new Tile("castle_pravo.png",false),
                new Tile("castle_levodole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_dole.png", false), new Tile("castle_spodniprava.png", false)
    };
    tileAligner(m_tiles5, grid_w, grid_h);

}

