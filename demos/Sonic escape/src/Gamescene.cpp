//
// Created by Teoman on 11/12/2019.
//
#include "Gamescene.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "sonicdata.h"
#include "shared.h"
#include "blockdata.h"
#include "gamescenebg.h"
#include <vector>
#include <cstdlib>
#include "sonicjump.h"
#include "sonicdeath.h"
#include "seashanty.h"

std::vector<Sprite *> Gamescene::sprites() {
    std::vector<Sprite *> sprites;
    sprites.push_back(sonicModel->getSpriteSonic());
    sprites.push_back(blockModel->getSpriteBlock());
    sprites.push_back(secondBlockModel->getSpriteBlock());
    return sprites;
}


std::vector<Background *> Gamescene::backgrounds() {
    std::vector<Background *> backgrounds;
    backgrounds.push_back(bg.get());
    return {backgrounds};
}

void Gamescene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(gamescenebgPal, sizeof(gamescenebgPal)));

    SpriteBuilder<Sprite> Builder;
    sonic = Builder
            .withData(sonicTiles, sizeof(sonicTiles))
            .withSize(SIZE_32_32)
            .withAnimated(6, 3)
            .withinBounds()
            .withLocation(30, GBA_SCREEN_HEIGHT / 2 + 8)
            .buildPtr();


    block = Builder
            .withData(blockTiles, sizeof(blockTiles))
            .withSize(SIZE_32_16)
            .withLocation(30, GBA_SCREEN_HEIGHT / 2 + 40)
            .buildPtr();

    secondBlock = Builder
            .withData(blockTiles, sizeof(blockTiles))
            .withSize(SIZE_32_16)
            .withLocation(80, GBA_SCREEN_HEIGHT / 2 - 60)
            .buildPtr();

    sonic->makeAnimated(0, 2, 15);
    sonicModel = std::unique_ptr<Sonic>(new Sonic(std::move(sonic)));
    isOnPlatform = 1;

    bg = std::unique_ptr<Background>(
            new Background(1, gamescenebgTiles, sizeof(gamescenebgTiles), gamescenebgMap, sizeof(gamescenebgMap)));
    bg.get()->useMapScreenBlock(16);

    blockModel = std::unique_ptr<Block>(new Block(std::move(block)));
    secondBlockModel = std::unique_ptr<Block>(new Block(std::move(secondBlock)));

    engine->enqueueMusic(seashanty, sizeof(seashanty), 16000);

}

int Gamescene::getIsOnPlatform() {

    if (sonicModel->getSpriteSonic()->getX() >=
        (blockModel->getSpriteBlock()->getX() - 16) &&
        (sonicModel->getSpriteSonic()->getX() + 16) <=
        (blockModel->getSpriteBlock()->getX() + 32)) {

        if (abs(blockModel->getSpriteBlock()->getY() - 32 - sonicModel->getSpriteSonic()->getY()) < 3) {
            isOnPlatform = 1;
        }
    } else if (sonicModel->getSpriteSonic()->getX() >= (secondBlockModel->getSpriteBlock()->getX() - 16) &&
               (sonicModel->getSpriteSonic()->getX() + 16) <= (secondBlockModel->getSpriteBlock()->getX() + 32)) {

        if (abs(secondBlockModel->getSpriteBlock()->getY() - 32 - sonicModel->getSpriteSonic()->getY()) < 5) {
            isOnPlatform = 2;
        }
    } else {
        isOnPlatform = 0;
    }
    return isOnPlatform;
}

void Gamescene::resetGame() {
    sonicModel->resetSonic();
    isOnPlatform = 1;
    sonicModel->setDood(false);
    sonic->makeAnimated(0, 2, 15);
    sonicModel->setOnPlatform(true);
    blockModel->getSpriteBlock()->moveTo(30, GBA_SCREEN_HEIGHT / 2 + 40);
    blockModel->setDx(1);

    secondBlockModel->getSpriteBlock()->moveTo(80, GBA_SCREEN_HEIGHT / 2 - 60);
    secondBlockModel->setDx(1);

    score = 0;
}

void Gamescene::fallDown() {
    if (isOnPlatform == 0) {
        sonicModel->setJumpingTick(30);
        sonicModel->setJumping(true);
    }
}

void Gamescene::followPlatform(){
    if (getIsOnPlatform() == 1) {
        sonicModel->getSpriteSonic()->setVelocity(blockModel->getDx(), 0);
    } else if (getIsOnPlatform() == 2) {
        sonicModel->getSpriteSonic()->setVelocity(secondBlockModel->getDx(), 0);
    } else if (getIsOnPlatform() == 0) {
        sonicModel->getSpriteSonic()->setVelocity(sonicModel->getDx(), +2);
    }
}
void Gamescene::tick(u16 keys) {
    if (sonicModel->getDood()) {
        sonicModel->getSpriteSonic()->stopAnimating();
        sonicModel->getSpriteSonic()->animateToFrame(12);
        engine->enqueueSound(sonicdeath, sizeof(sonicdeath), 16000);
        if (keys & KEY_START) {
            resetGame();
        }
    } else {
        TextStream::instance().setText(std::string("Score:") + std::to_string(score), 1, 1);
        if (sonicModel->getDx() > 0) {
            scrollX++;
        } else if (sonicModel->getDx() < 0) {
            scrollX--;
        }
        bg.get()->scroll(scrollX, 0);

        if (blockModel->getSpriteBlock()->getY() == 160) {
            blockModel->getSpriteBlock()->moveTo(rand() % 120 + 20, secondBlockModel->getSpriteBlock()->getY() - 100);
            if (score > 5) {
                blockModel->setDx(2);
            }
            if (score > 10) {
                blockModel->setDx(3);
            }
            if (score > 15) {
                blockModel->setDx(4);
            }
            if (score > 20) {
                blockModel->setDx(5);
            }
            if (score > 25) {
                blockModel->setDx(6);
            }
        }
        if (blockModel->getSpriteBlock()->getX() + 52 > GBA_SCREEN_WIDTH) {
            blockModel->setDx(blockModel->getDx() * -1);
        } else if (blockModel->getSpriteBlock()->getX() < 20) {
            blockModel->setDx(blockModel->getDx() * -1);
        }

        if (secondBlockModel->getSpriteBlock()->getX() + 52 > GBA_SCREEN_WIDTH) {
            secondBlockModel->setDx(secondBlockModel->getDx() * -1);
        } else if (secondBlockModel->getSpriteBlock()->getX() < 20) {
            secondBlockModel->setDx(secondBlockModel->getDx() * -1);
        } else if (secondBlockModel->getSpriteBlock()->getY() == 160) {
            secondBlockModel->getSpriteBlock()->moveTo((rand() % 120) + 20, blockModel->getSpriteBlock()->getY() - 100);
            if (score > 5) {
                secondBlockModel->setDx(2);
            }
            if (score > 10) {
                secondBlockModel->setDx(3);
            }
            if (score > 15) {
                secondBlockModel->setDx(4);
            }
            if (score > 20) {
                secondBlockModel->setDx(5);
            }
            if (score > 25) {
                secondBlockModel->setDx(6);
            }
        }

        sonicModel->tick();
        blockModel->tick();
        secondBlockModel->tick();

        if (!sonicModel->getOnPlatform()) {
            blockModel->setDy(0);
            secondBlockModel->setDy(0);
        }

        if (sonicModel->getDy() == 2) {

            if (sonicModel->getSpriteSonic()->getX() >=
                (blockModel->getSpriteBlock()->getX() - 16) &&
                (sonicModel->getSpriteSonic()->getX() + 16) <=
                (blockModel->getSpriteBlock()->getX() + 32)) {

                if (abs(blockModel->getSpriteBlock()->getY() - 32 - sonicModel->getSpriteSonic()->getY()) < 1) {
                    sonicModel->setOnPlatform(true);
                    score++;
                }
            }

            if (sonicModel->getSpriteSonic()->getX() >=
                (secondBlockModel->getSpriteBlock()->getX() - 16) &&
                (sonicModel->getSpriteSonic()->getX() + 16) <=
                (secondBlockModel->getSpriteBlock()->getX() + 32)) {

                if (abs(secondBlockModel->getSpriteBlock()->getY() - 32 - sonicModel->getSpriteSonic()->getY()) < 1) {
                    sonicModel->setOnPlatform(true);
                    score++;
                }

            }
        }

        if (sonicModel->getJumpingTick() > 0 && sonicModel->getJumpingTick() < 21) {
            blockModel->setDy(+5);
            secondBlockModel->setDy(+5);
        }

        if (!sonicModel->getJumping()) {
            blockModel->setDy(0);
            secondBlockModel->setDy(0);
        }
    }

    if (sonicModel->getOnPlatform()) {
        if (keys & KEY_LEFT) {
            sonicModel->setDx(-1);
            fallDown();
        } else if (keys & KEY_RIGHT) {
            sonicModel->setDx(1);
            fallDown();
        } else {
            followPlatform();
        }
    }

    if (keys & KEY_LEFT) {
        if ((sonicModel->getDx() == 0)) {
            sonicModel->setDx(-1);
        }
        if (keys & KEY_A) {
            engine->enqueueSound(sonicjump, sizeof(sonicjump), 16000);
            sonicModel->startJump();

        }
    } else if (keys & KEY_RIGHT) {
        if ((sonicModel->getDx() == 0)) {
            sonicModel->setDx(1);

        }
        if (keys & KEY_A) {
            engine->enqueueSound(sonicjump, sizeof(sonicjump), 16000);
            sonicModel->startJump();

        }
    } else if (keys & KEY_UP) {
        sonicModel->setDy(-1);
    } else if (keys & KEY_DOWN) {
        sonicModel->setDy(1);
    } else if (keys & KEY_A) {
        engine->enqueueSound(sonicjump, sizeof(sonicjump), 16000);
        sonicModel->startJump();

    } else {
        sonicModel->setDx(0);
        sonicModel->setDy(0);
    }
}
