#ifndef __GAME_HEADER__
#define __GAME_HEADER__

// TODO: Maybe move to a singleton with these as public?
namespace gh
{
    // Statics
    static const int GH_SCREEN_W = 1024;
    static const int GH_SCREEN_H = 768;
    static const int GH_SCREEN_W_HALF = GH_SCREEN_W / 2;
    static const int GH_SCREEN_H_HALF = GH_SCREEN_H / 2;
    static const float GH_SCREEN_W_HALF_F = float(GH_SCREEN_W_HALF);
    static const float GH_SCREEN_H_HALF_F = float(GH_SCREEN_H_HALF);
    static const float GH_PLAYER_SPEED = 8.0F; // no decimal digits (beware large numbers to prevent player skipping... or decrease fixed delta)
    //static const float GH_FL_ZERO = 0.00001F;
    static const int GH_HOTBAR_SIZE = 2;
    static const int GH_DEFAULT_OBJECT_SIZE = 1;
    static const int GH_DEFAULT_OBJECT_VISUAL_SIZE = 32;
    static const int GH_DEFAULT_TILE_SIZE = 1;
    static const float GH_DEFAULT_TILE_SIZE_F = 1.0F;
    static const int GH_DEFAULT_TILE_VISUAL_SIZE = 32;
    static const float GH_DEFAULT_TILE_VISUAL_SIZE_F = float(GH_DEFAULT_TILE_VISUAL_SIZE);
    static const int GH_TILES_INIT_SHIFT_X = 32;
    static const int GH_TILES_INIT_SHIFT_Y = 32;
    static const float GH_DEFAULT_PROJECTILE_SIZE = 0.125F;
    static const int GH_DEFAULT_PROJECTILE_VISUAL_SIZE = 4;
    static const float GH_DEFAULT_PROJECTILE_SPD = 1.0F;
    static const float GH_DEFAULT_PROJECTILE_SPD_MUL = 8.0F;
    static const int GH_DEFAULT_PROJECTILE_DIST_LIM = 2;
    static const int GH_MONSTER_ATTACK_COOLDOWN = 1; // In seconds
    static const float GH_MAX_DISTANCE_FOR_CLICKABLE_OBJECTS = 4.0F;
    static const int GH_INVENTORY_WIDTH = 7;
    static const int GH_INVENTORY_HEIGHT = 7;

    extern float GH_ENTITY_VOLUME;

    // the lower the vaule is the more updates per second will physics run.
    // Disadvantages: With extremely low values there can be problem with timers because dividing by zero for each physics frame is bad idea
    //                Example: 0.02 is 50x a second. 3m/s is 3 / 50 = 0,06. That means we need to do 50x0,06m a second to get 3m/s.
    //                         For STATIC_UPDATE = 0,0002 the 3m/s is 3 / 5000 = 0,0006. That means we need to do 5000x0,0006m a second to get 3m/s.
    // So the simplest way to calculate fixed delta is: 1 / (required repeat rate per sec) -> 1 / 50 = 0.02
    // the lower the number is the more precise physics calculations are but also the more proccessing power it will take (more physics updates per sec)
    static const float GH_FIXED_DELTA_TIME = 0.01F;//0.02F; // in seconds
}


#endif
