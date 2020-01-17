//
// Created by Teoman on 6/01/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BLOCK_H
#define GBA_SPRITE_ENGINE_PROJECT_BLOCK_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Block {
private:
    std::unique_ptr<Sprite> block;
    int dx = 1;
    int dy = 0;

public:
    Block(std::unique_ptr<Sprite> sprite1) : block(std::move(sprite1)) {};
    void setDx(int dir);
    void setDy(int dir);
    int getDx();
    int getDy();
    Sprite* getSpriteBlock() {return block.get();}
    void tick();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BLOCK_H
