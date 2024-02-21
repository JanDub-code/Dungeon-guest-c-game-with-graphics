#ifndef __SCENE__
#define __SCENE__

// TODO: or Level?

#include <QObject>
#include <QVariant>
#include <QMediaPlayer>
#include "camera.h"
#include "player.h"
#include "object.h"
#include "tilegenerator.h"

// TODO: Rework to .json
class BaseScene// : public QObject
{
    //Q_OBJECT
    //Q_PROPERTY(QVariant objects READ getObjects NOTIFY objVecResized)
protected:
    //v_objects m_objects; // INFO: variables of type shared_ptr must be cleared in order to be removed totaly
    //Player *m_player;
    //Inventory *m_inventory;
    //Hotbar *m_hotbar;
    //Camera *m_camera;
    v_objects m_objects;
    //static v_objects m_cache;
    bool m_loaded; // TODO: If not loaded then load in game engine. If already loaded then load from save (to prevent refreshing objects and keep old map)
public:
    // TODO: emit when scene is changed
    BaseScene();
    virtual ~BaseScene();
    // Load all necessary objects
    //virtual void initScene() = 0; // TODO: Swap with loadScene because loadScene could be used to load existing scene (inited and manipulated scene)
    virtual void initScene(Player *player, Camera *cam, std::vector<Tile*> *&tiles, tileGenerator &tg) = 0; // loads to &objects only
    virtual void loadAmbientMusic(QMediaPlayer &amb_mus) = 0;
    void clearContents();
    //QVariant getObjects();

    inline v_objects *getContents()
    {
        //m_cache = m_objects;
        //return &m_cache;
        return &m_objects;
    }
    inline bool isLoaded()
    { return m_loaded; }
    //virtual void loadScripts() = 0;

    //void saveScene(v_objects &objects, Player &player, Camera &cam)
    //{ m_objects = objects; m_player = player; m_camera = camera; } // saves to local m_objects

    //void discard() { clear.m_objects(); } // clears local m_objects
    //void loadSaved(v_objects &objects, Player &player, Camera &cam) { objects = m_objects; }
//signals:
    //void objVecResized();
};

#endif
