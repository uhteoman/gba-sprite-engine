//
// Created by Teoman on 27/12/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SONIC_H
#define GBA_SPRITE_ENGINE_PROJECT_SONIC_H
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>

class Sonic {

private:
    std::unique_ptr<Sprite> sonic;
    int dx = 0;
    int dy = 0;
    bool turn = false;
    bool dood = false;
    bool jumping = false;
    int jumpingTick;
    bool onPlatform = true;

public:

    Sonic(std::unique_ptr<Sprite> sprite1) : sonic(std::move(sprite1)) {};
    void setDx(int dir);
    void setDy(int dir);
    void setJumping(bool);
    void setJumpingTick(int tick);
    int getDx();
    int getDy();
    bool getJumping();
    void setOnPlatform(bool);
    bool getOnPlatform();
    int getJumpingTick();
    void setDood(bool input);
    bool getDood();
    void move();
    void jumpMove();
    void startJump();
    void endJump();
    void resetSonic();
    void tick();
    Sprite* getSpriteSonic() { return sonic.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SONIC_H
