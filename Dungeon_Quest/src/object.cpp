#include "object.h"
#include "game_header.h"


Object::Object(QObject *parent) : QObject(parent)
{
    m_debug_in_collision = false;
    m_pos = Vec2f(0.0F, 0.0F);
    m_name = "object";
    m_texture = "";
    //m_size = Vec2f(float(gh::GH_DEFAULT_OBJECT_SIZE));
    m_visual_size = Vec2i(gh::GH_DEFAULT_OBJECT_VISUAL_SIZE);
    m_orientation = ObjOrientation::OO_RIGHT;
    m_quest_status = QuestStatus::QS_NONE;
    m_visible = true;
    m_photo = "";
}

Object::~Object()
{
}

void Object::update()
{
    /*emit posChanged();*/
}

void Object::fixedUpdate()
{
    //emit posChanged();
}

float Object::getQMLPosX()
{
    return m_pos.x;
}

float Object::getQMLPosY()
{
    return m_pos.y;
}

void Object::cameraMoveToObj(Camera *cam)
{
    // if object out of borders move cam pos + exceeded obj pos to border
    // TODO: Refactor and check for errors
    if (m_pos.x > cam->getPos().x + cam->getBorderX())
    {
        cam->move(Vec2f(m_pos.x - (cam->getPos().x + cam->getBorderX()), 0.0F));
        cam->setPosChanged();
    }
    if (m_pos.x < cam->getPos().x - cam->getBorderX())
    {
        cam->move(Vec2f(-(cam->getPos().x - cam->getBorderX() - m_pos.x), 0.0F));
        cam->setPosChanged();
    }
    if (m_pos.y > cam->getPos().y + cam->getBorderY())
    {
        cam->move(Vec2f(0.0F, m_pos.y - (cam->getPos().y + cam->getBorderY())));
        cam->setPosChanged();
    }
    if (m_pos.y < cam->getPos().y - cam->getBorderY())
    {
        cam->move(Vec2f(0.0F, -((cam->getPos().y - cam->getBorderY()) - m_pos.y)));
        cam->setPosChanged();
    }
}

void Object::setName(std::string name)
{
    m_name = name;
    emit nameChanged();
}

void Object::setQName(QString name)
{
    m_name = name.toStdString();
    emit nameChanged();
}

std::string Object::getName() const
{
    return m_name;
}

void Object::setTexture(std::string texture)
{
    m_texture = QString::fromStdString("assets/" + texture);
    emit textureChanged();
}

QString Object::getTexture()
{
    return m_texture;
}

void Object::setVisible()
{
    m_visible = true;
    emit visibilityChanged();
}

void Object::setInvisible()
{
    m_visible = false;
    emit visibilityChanged();
}

bool Object::isVisible()
{
    return m_visible;
}

QString Object::getQName()
{
    return QString::fromStdString(m_name);
}

int Object::getVisualWidth()
{
    return m_visual_size.x;
}

int Object::getVisualHeight()
{
    return m_visual_size.y;
}

void Object::setQuestState(QuestStatus quest_status)
{
    m_quest_status = quest_status;
    emit questStatusChanged();
}

void Object::setPhoto(std::string photo)
{
    m_photo = QString::fromStdString(photo);
}


QString Object::getPhoto() const
{
    return m_photo;
}

#if 0
float Object::getRectOriginX()
{
    return (m_pos.x + (m_size.x / 2.0F));
}

float Object::getRectOriginY()
{
    return (m_pos.y + (m_size.y / 2.0F));
}
#endif
