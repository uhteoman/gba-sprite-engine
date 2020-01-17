//
// Created by Teoman on 6/01/2020.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "Block.h"

int Block::getDx() {
    return dx;
}

int Block::getDy() {
    return dy;
}

void Block::setDy(int dir) {
    dy = dir;
}

void Block::setDx(int dir) {
    dx = dir;
}

void Block::tick() {
    getSpriteBlock()->setVelocity(dx, dy);
    getSpriteBlock()->animateToFrame(0);

}