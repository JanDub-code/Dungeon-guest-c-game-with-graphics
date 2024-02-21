#include "tile.h"
#include "game_header.h"
//#include "camera.h"
#include <map>

const std::map<std::string, int> Tile::aabb_img_dbs =
{
    {"schody000.png", 0},
    {"schody001.png", 1},
    {"schody002.png", 2},
    {"schody003.png", 3},
    {"schody004.png", 4},
    {"schody005.png", 5},
};

Tile::Tile(QObject *parent) : QObject(parent), m_untouchable(true)
{
    m_pos = Vec2f(0.0F);
    m_z = 0;
    m_visual_size = Vec2i(gh::GH_DEFAULT_TILE_VISUAL_SIZE);
    m_aabb = AABB(m_pos, Vec2f(float(gh::GH_DEFAULT_TILE_SIZE)));
    m_photo="void.png";
}
#if 0
Tile::Tile(const QString &photo) : QObject(), m_isWalkable(true), m_photo(photo)
{
    m_pos = Vec2f(0.0F);
    m_size = Vec2f(float(gh::GH_DEFAULT_TILE_SIZE));
    m_aabb = AABB(&m_pos, &m_size);
}
#endif
Tile::Tile(const QString &photo, bool untouchable, int z) : QObject(), m_untouchable(untouchable), m_photo(photo), m_z(z)
{
    m_pos = Vec2f(0.0F);
    m_aabb = getAabbBasedOnImageDatabase(photo);
}

QString Tile::getPhoto() const
{
    return m_photo;
}

bool Tile::isTouchable() const
{
    return !m_untouchable;
}

void Tile::setZHeight(int z)
{
    m_z = z;
    emit zHeightChanged();
}

AABB Tile::getAabbBasedOnImageDatabase(const QString &photo)
{
    std::string temp = photo.toStdString();

    if (aabb_img_dbs.count(temp) > 0)
    {
        Vec2f stairs_right = Vec2f(0.75F, 0.0F);

        switch (aabb_img_dbs.find(temp)->second) {
        case 0:
            return AABB(m_pos, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        case 1:
            return AABB(m_pos + stairs_right, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        case 2:
            return AABB(m_pos, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        case 3:
            return AABB(m_pos + stairs_right, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        case 4:
            return AABB(m_pos, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        case 5:
            return AABB(m_pos + stairs_right, Vec2f(0.25F, gh::GH_DEFAULT_TILE_SIZE_F));
        default:
            return AABB(m_pos, Vec2f(gh::GH_DEFAULT_TILE_SIZE_F)); // Probably will never happen
        }
    }

    return AABB(m_pos, Vec2f(gh::GH_DEFAULT_TILE_SIZE_F));
}
