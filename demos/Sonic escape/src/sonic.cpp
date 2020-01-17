//
// Created by Teoman on 27/12/2019.
//
#include <libgba-sprite-engine/gba_engine.h>
#include "sonic.h"
#include "sonicdeath.h"
void Sonic::setDx(int dir){
    dx = dir;
}

void Sonic::setDy(int dir) {
    dy = dir;
}

void Sonic::setJumping(bool isJumping) {
    jumping = isJumping;
}

void Sonic::setJumpingTick(int tick) {
    jumpingTick = tick;
}

int Sonic::getDx() {
    return dx;
}

int Sonic::getDy() {
    return dy;
}

bool Sonic::getJumping() {
    return jumping;
}

int Sonic::getJumpingTick() {
    return jumpingTick;
}

void Sonic::setDood(bool input) {
    dood = input;
}

bool Sonic::getDood() {
    return dood;
}

void Sonic::resetSonic() {
    getSpriteSonic()->moveTo(30, GBA_SCREEN_HEIGHT / 2 + 8);
    getSpriteSonic()->makeAnimated(0, 2, 15);

}


void Sonic::startJump() {
    jumping = true;
    onPlatform = false;
}

void Sonic::setOnPlatform(bool input) {
    onPlatform = input;
    endJump();
}

bool Sonic::getOnPlatform() {
    return onPlatform;
}

void Sonic::endJump() {
    setJumping(false);
    jumpingTick=0;
}

void Sonic::move() {
    if (getDx() == 1) {
        getSpriteSonic()->setVelocity(+3, 0);
        getSpriteSonic()->animateToFrame(3);
        turn = false;
    } else if (getDx() == -1) {
        getSpriteSonic()->setVelocity(-3, 0);
        getSpriteSonic()->animateToFrame(3);
        turn = true;
    } else {
        getSpriteSonic()->setVelocity(0, 0);
        getSpriteSonic()->animateToFrame(0);
    }
}

void Sonic::jumpMove() {
    if (jumpingTick<=(25)) {
        if (dx == 1) {
            getSpriteSonic()->setVelocity(2, -1);
            getSpriteSonic()->animateToFrame(3);
            turn = false;
            jumpingTick++;
        }
        else if (dx == -1) {
            getSpriteSonic()->setVelocity(-2, -1);
            getSpriteSonic()->animateToFrame(3);
            turn = true;
            jumpingTick++;
        }

        else {
            getSpriteSonic()->setVelocity(0, -1);
            getSpriteSonic()->animateToFrame(3);
            jumpingTick++;
        }
    }

    else if (jumpingTick>(25)){
        setDy(2);
        if (dx == 1) {
            getSpriteSonic()->setVelocity(2, dy);
            getSpriteSonic()->animateToFrame(3);
            turn = false;
            jumpingTick++;
        }
        else if (dx == -1) {
            getSpriteSonic()->setVelocity(-2, dy);
            getSpriteSonic()->animateToFrame(3);
            turn = true;
            jumpingTick++;
        }

        else if (dx == 0) {
            getSpriteSonic()->setVelocity(0, dy);
            jumpingTick++;
        }
    }
}

void Sonic::tick() {
    getSpriteSonic()->flipHorizontally(turn);

    if (!getJumping()) {
        jumpingTick=0;
        move();
    }

    else if (getJumping()) {
        onPlatform = false;
        jumpMove();
    }

    if (getSpriteSonic()->getY() >= GBA_SCREEN_HEIGHT / 2 + 35) {
        endJump();
        setDood(true);
    }
}


